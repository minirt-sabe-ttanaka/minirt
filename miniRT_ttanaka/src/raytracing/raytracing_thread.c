/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:21:08 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 00:51:26 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/raytracing.h"

int		take_new_line(t_renderer *r);
void	*render_thread(void *arg);
void    transfer_to_image(t_scene *scene, t_pixel_data *buf, int w, int h);

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
	int				x;
	int				y;
	unsigned int	seed;
	int				idx;

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
			idx = y * data->renderer->scene->screen_width + x;
			data->geo_buffer[idx].color = sampling_ray(data->renderer->scene,
					data->renderer->cam, x, y, &seed);
			get_gbuffer_info(data->renderer->scene, data->renderer->cam, x, y, &data->geo_buffer[idx]);
		}
	}
	return (NULL);
}

void    transfer_to_image(t_scene *scene, t_pixel_data *buf, int width, int height)
{
    int         x;
    int         y;
    t_color3    c;

    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            c = buf[y * width + x].color;
            my_mlx_pixel_put(scene, x, y, tcolor2rgb(c));
            x++;
        }
        y++;
    }
}
