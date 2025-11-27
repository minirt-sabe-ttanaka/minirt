/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:02:49 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 15:13:57 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../get_next_line/get_next_line.h"
# include "scene.h"
# include "scene/hittable.h"
# include "scene/hittable/shape.h"
# include "scene/material.h"
# include "rt_struct.h"
# include <fcntl.h>
# include <stdlib.h>

# define ERRMSG_FILENAME "Error: filename extension must be \".rt\"."
# define EXIT_EMPTY 2
# define EXIT_ERROR 3
# define EPS 1e-2

typedef enum e_element_type
{
	ambient_lighting,
	camera,
	light,
	sphere,
	plane,
	cylinder,
	empty,
	error
}		t_element_type;

bool	parse_color_format(char *s, t_color3 *color);

bool	parse_coords_format(char *s, t_color3 *point);

bool	parse_double(char *s, double *val);

bool	parse_material_format(char *color, char *type, char *param,
			t_material_config *config);
bool	create_material(t_material_config *m_config, t_material *material);

bool	read_lines_loop(int fd, t_scene *scene);
bool	check_extension(char *path);
bool	parse_file(char *path, t_scene *scene);
bool	create_scene(char *path, t_scene *scene);

bool	set_ambient(char **splitted_data, t_scene *scene);
bool	set_camera(char **splitted_data, t_scene *scene);
bool	set_light(char **splitted_data, t_scene *scene);
bool	set_sphere(char **splitted_data, t_scene *scene);
bool	set_plane(char **splitted_data, t_scene *scene);
bool	set_cylinder(char **splitted_data, t_scene *scene);

void	notify_err_line_content(char *s);

#endif