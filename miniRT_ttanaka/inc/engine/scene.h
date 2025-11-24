/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:02:43 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:15:47 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "core/utils.h"
# include "engine/camera.h"
# include "scene/hittable.h"
# include "struct.h"

typedef struct s_ambient
{
	double			ratio;
	t_color3		color;
}					t_ambient;

typedef struct s_light
{
	t_point3		origin;
	double			ratio;
	t_color3		color;
}					t_light;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_hittable		*bvh;
	t_hittable_lst	*objects;
	bool			ambient_initialized;
	bool			camera_initialized;
	bool			light_initialized;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				screen_width;
	int				screen_height;
}					t_scene;

#endif