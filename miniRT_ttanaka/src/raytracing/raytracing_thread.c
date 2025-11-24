#include "raytracing.h"

int		take_new_line(t_renderer *r);
void	*render_thread(void *arg);

int	take_new_line(t_renderer *r)
{
	int	y;

	pthread_mutex_lock(&(r->update_mutex));
	y = r->next_y;
	if (y < r->scene->screen_height)
	{
		r->next_y++;
		display_progress_bar(r->next_y, r->scene->screen_height);
	}
	pthread_mutex_unlock(&(r->update_mutex));
	return (y);
}

void	*render_thread(void *arg)
{
	t_thread_data	*data;
	t_color3		pixel_color;
	int				x;
	int				y;
	unsigned int	seed;

	data = (t_thread_data *)arg;
	seed = init_seed() + (data->id * 12345);
	while (1)
	{
		y = take_new_line(data->renderer);
		if (y >= data->renderer->scene->screen_height)
			break ;
		x = -1;
		while (++x < data->renderer->scene->screen_width)
		{
			pixel_color = sampling_ray(data->renderer->scene,
					data->renderer->cam, x, y, &seed);
			my_mlx_pixel_put(data->renderer->scene, x, y,
				tcolor2rgb(pixel_color));
		}
	}
	return (NULL);
}
