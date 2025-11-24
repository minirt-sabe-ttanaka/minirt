#include "raytracing.h"

void		display_progress_bar(int current, int total);
t_color3	calc_direct_light(t_scene *scene, t_hit_record *rec,
				t_color3 albedo);
t_color3	ray_color(const t_ray *r, t_scene *scene, int depth,
				unsigned int *seed);
t_color3	sampling_ray(t_scene *scene, t_camera *cam, int x, int y,
				unsigned int *seed);

void	display_progress_bar(int current, int total)
{
	double	percent;
	int		filled_len;
	int		i;

	if (total == 0)
		return ;
	percent = (double)current / total;
	filled_len = (int)(BAR_WIDTH * percent);
	write(STDOUT_FILENO, "\r", 1);
	write(STDOUT_FILENO, "[", 1);
	i = -1;
	while (++i < BAR_WIDTH)
	{
		if (i < filled_len)
			write(STDOUT_FILENO, "=", 1);
		else if (i == filled_len)
			write(STDOUT_FILENO, ">", 1);
		else
			write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, "] ", 2);
	ft_putnbr_fd((int)(percent * 100.0), STDOUT_FILENO);
	write(STDOUT_FILENO, "%", 1);
	if (current == total)
		write(STDOUT_FILENO, "\n", 1);
}

t_color3	calc_direct_light(t_scene *scene, t_hit_record *rec,
		t_color3 albedo)
{
	t_vec3			light_dir;
	double			dist;
	double			cos_theta;
	t_ray			shadow_ray;
	t_hit_record	tmp_rec;

	light_dir = vec_sub(scene->light.origin, rec->p);
	dist = vec_norm(light_dir);
	light_dir = vec_normalize(light_dir);
	shadow_ray = ray_init(vec_add(rec->p, vec_scale(rec->normal, SHADOW_BIAS)),
			light_dir);
	if (scene->bvh && scene->bvh->vtable->hit(scene->bvh->object, &shadow_ray,
			SHADOW_BIAS, dist - SHADOW_BIAS, &tmp_rec))
		return (color_init(0, 0, 0));
	cos_theta = vec_dot(rec->normal, light_dir);
	if (cos_theta < 0)
		return (color_init(0, 0, 0));
	return (vec_scale(vec_mult(albedo, vec_scale(scene->light.color,
					scene->light.ratio)), cos_theta));
}

t_color3	ray_color(const t_ray *r, t_scene *scene, int depth,
		unsigned int *seed)
{
	t_hit_record	rec;
	t_color3		emitted;
	t_color3		direct_light;
	t_color3		indirect_light;
	t_scatter_ctx	ctx;

	if (depth <= 0)
		return (vec_scale(scene->ambient.color, scene->ambient.ratio));
	if (!scene->bvh || !scene->bvh->vtable->hit(scene->bvh->object, r, 0.001,
			100000.0, &rec))
	{
		return (vec_scale(scene->ambient.color, scene->ambient.ratio));
	}
	emitted = rec.mat.vtable->emitted(rec.mat.object, 0, 0, &rec.p);
	ctx.r_in = r;
	ctx.rec = &rec;
	ctx.seed = seed;
	if (!rec.mat.vtable->scatter(rec.mat.object, &ctx))
		return (emitted);
	direct_light = calc_direct_light(scene, &rec, ctx.attenuation);
	indirect_light = vec_mult(ctx.attenuation, ray_color(&(ctx.scattered), scene, depth
				- 1, seed));
	return (vec_add(emitted, vec_add(direct_light, indirect_light)));
}

t_color3	sampling_ray(t_scene *scene, t_camera *cam, int x, int y,
		unsigned int *seed)
{
	t_color3 pixel_color;
	double u;
	double v;
	int s;
	t_ray r;

	pixel_color = color_init(0, 0, 0);
	s = 0;
	while (s < SAMPLE_PER_PIXEL)
	{
		u = (x + random_double(seed)) / (scene->screen_width - 1);
		v = (scene->screen_height - 1 - y + random_double(seed))
			/ (scene->screen_height - 1);
		r = camera_get_ray(cam, u, v);
		pixel_color = color_add(pixel_color, ray_color(&r, scene, MAX_DEPTH,
					seed));
		s++;
	}
	return (color_init(ft_clamp(sqrt(pixel_color.r / SAMPLE_PER_PIXEL), 0, 1),
			ft_clamp(sqrt(pixel_color.g / SAMPLE_PER_PIXEL), 0, 1),
			ft_clamp(sqrt(pixel_color.b / SAMPLE_PER_PIXEL), 0, 1)));
}