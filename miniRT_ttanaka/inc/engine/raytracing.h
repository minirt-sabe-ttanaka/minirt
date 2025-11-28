/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:02:16 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 01:09:11 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "core/utils.h"
# include "engine/plot.h"
# include "rt_struct.h"
# include "scene.h"
# include "scene/hittable.h"
# include <pthread.h>
# define BAR_WIDTH 50
# define MAX_DEPTH 10
# define SAMPLE_PER_PIXEL 50
# define NUM_THREADS 8
# define SIGMA_C 0.01
# define SIGMA_N 128.0
# define SIGMA_P 0.1

typedef struct s_pixel_data
{
	t_color3		color;
	t_vec3			normal;
	t_point3		position;
	double			depth;
}					t_pixel_data;

int					raytracing(t_scene *scene, t_camera *cam);

void				display_progress_bar(int current, int total);
t_color3			calc_direct_light(t_scene *scene, t_hit_record *rec,
						t_color3 albedo);
t_color3			ray_color(const t_ray *r, t_scene *scene, int depth,
						unsigned int *seed);
t_color3			sampling_ray(t_scene *scene, t_camera *cam, int x, int y,
						unsigned int *seed);
void				get_gbuffer_info(t_scene *scene, t_camera *cam, int x,
						int y, t_pixel_data *data);

typedef struct s_renderer
{
	t_scene			*scene;
	t_camera		*cam;
	int				next_y;
	pthread_mutex_t	update_mutex;
}					t_renderer;

typedef struct s_thread_data
{
	t_renderer		*renderer;
	int				id;
	t_pixel_data	*geo_buffer;
}					t_thread_data;

int					take_new_line(t_renderer *r);
void				*render_thread(void *arg);

void				apply_denoise(t_pixel_data *buffer, int screen_width,
						int screen_height);
void				transfer_to_image(t_scene *scene, t_pixel_data *buf, int w,
						int h);
#endif
