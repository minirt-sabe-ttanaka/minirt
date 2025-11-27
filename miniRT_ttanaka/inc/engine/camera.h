/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:01:44 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 15:13:57 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "core/ray.h"
# include "core/utils.h"
# include "rt_struct.h"

typedef struct s_camera
{
	t_point3	orig;
	t_point3	lower_left_corner;
	t_vec3		horizontal;
	t_vec3		vertical;
}				t_camera;

typedef struct s_camera_config
{
	t_point3	look_from;
	t_point3	look_to;
	t_point3	vup;
	double		fov;
	double		aspect_ratio;
}				t_camera_config;

void			camera_init(t_camera *cam, t_camera_config *config);
t_ray			camera_get_ray(const t_camera *cam, double u, double v);

#endif