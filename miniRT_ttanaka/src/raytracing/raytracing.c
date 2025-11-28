/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:21:18 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 23:52:36 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/raytracing.h"

int	raytracing(t_scene *scene, t_camera *cam)
{
	t_pixel_data	*geo_buffer;
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	t_renderer		renderer;
	int				i;
	int 			size;

	size = scene->screen_height * scene->screen_width;
	geo_buffer = malloc(sizeof(t_pixel_data) * size);
	if (!geo_buffer)
		return (EXIT_FAILURE);
	renderer.scene = scene;
	renderer.cam = cam;
	renderer.next_y = 0;
	if (pthread_mutex_init(&renderer.update_mutex, NULL))
	{
		free(geo_buffer);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].id = i;
		thread_data[i].renderer = &renderer;
		thread_data[i].geo_buffer = geo_buffer;
		if (pthread_create(&threads[i], NULL, render_thread, &thread_data[i]))
		{
			free(geo_buffer);
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
		pthread_join(threads[i++], NULL);
	apply_denoise(geo_buffer, scene->screen_width, scene->screen_height);
	transfer_to_image(scene, geo_buffer, scene->screen_width, scene->screen_height);
	free(geo_buffer);
	pthread_mutex_destroy(&renderer.update_mutex);
	return (EXIT_SUCCESS);
}
