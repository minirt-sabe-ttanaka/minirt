#include "engine/raytracing.h"

void			apply_denoise(t_pixel_data *buffer, int screen_width,
					int screen_height);

static double	get_kernel_weight(int i, int j)
{
	static const double	k[] = {1.0 / 256, 1.0 / 64, 3.0 / 128, 1.0 / 64, 1.0
			/ 256, 1.0 / 64, 1.0 / 16, 3.0 / 32, 1.0 / 16, 1.0 / 64, 3.0 / 128,
			3.0 / 32, 9.0 / 64, 3.0 / 32, 3.0 / 128, 1.0 / 64, 1.0 / 16, 3.0
			/ 32, 1.0 / 16, 1.0 / 64, 1.0 / 256, 1.0 / 64, 3.0 / 128, 1.0 / 64,
			1.0 / 256};

	return (k[(j + 2) * 5 + (i + 2)]);
}

static double	compute_weight(t_pixel_data *p, t_pixel_data *q, double k_val)
{
	double	w_c;
	double	w_n;
	double	w_p;

	if (vec_norm_squared(p->normal) < 1e-6
		|| vec_norm_squared(q->normal) < 1e-6)
	{
		if (p->depth == q->depth)
			return (k_val);
		else
			return (0.0);
	}
	w_c = exp(-vec_norm_squared(vec_sub(p->color, q->color)) / SIGMA_C);
	w_n = pow(fmax(0, vec_dot(p->normal, q->normal)), SIGMA_N);
	w_p = exp(-vec_norm(vec_sub(p->position, q->position)) / SIGMA_P);
	return (w_c * w_n * w_p * k_val);
}

static t_color3	denoise_pixel(t_pixel_data *src, int x, int y, int step,
		t_scene *scene)
{
	int			i;
	int			j;
	t_color3	sum_col;
	double		sum_w;
	double		w;
	int			idx[2];

	sum_col = color_init(0, 0, 0);
	sum_w = 0.0;
	j = -3;
	while (++j <= 2)
	{
		i = -3;
		while (++i <= 2)
		{
			idx[0] = x + i * step;
			idx[1] = y + j * step;
			if (idx[0] >= 0 && idx[0] < scene->screen_width && idx[1] >= 0
				&& idx[1] < scene->screen_height)
			{
				w = compute_weight(&src[y * scene->screen_width + x],
						&src[idx[1] * scene->screen_width + idx[0]],
						get_kernel_weight(i, j));
				sum_col = vec_add(sum_col, vec_scale(src[idx[1]
							* scene->screen_width + idx[0]].color, w));
				sum_w += w;
			}
		}
	}
	return (vec_scale(sum_col, 1.0 / sum_w));
}

void	eaw_pass(t_pixel_data *src, t_pixel_data *dst, int step, t_scene *scene)
{
	int	x;
	int	y;
	int	idx;

	y = 0;
	while (y < scene->screen_height)
	{
		x = 0;
		while (x < scene->screen_width)
		{
			idx = y * scene->screen_width + x;
			dst[idx] = src[idx];
			dst[idx].color = denoise_pixel(src, x, y, step, scene);
			x++;
		}
		y++;
	}
}

void	apply_denoise(t_pixel_data *buffer, int screen_width, int screen_height)
{
	t_pixel_data	*temp;
	int				step;
	int				iter;
	t_scene			dummy_scn;

	temp = malloc(sizeof(t_pixel_data) * screen_width * screen_height);
	if (!temp)
		return ;
	dummy_scn.screen_width = screen_width;
	dummy_scn.screen_height = screen_height;
	step = 1;
	iter = 0;
	while (iter < 5)
	{
		eaw_pass(buffer, temp, step, &dummy_scn);
		ft_memcpy(buffer, temp, sizeof(t_pixel_data) * screen_width
			* screen_height);
		step *= 2;
		iter++;
	}
	free(temp);
}
