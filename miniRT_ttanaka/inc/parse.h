#ifndef PARSE_H
# define PARSE_H

# include "../get_next_line/get_next_line.h"
# include "hittable.h"
# include "material.h"
# include "scene.h"
# include "shape.h"
# include <fcntl.h>
# include <stdlib.h>

# define ERRMSG_FILENAME "Error: filename extension must be \".rt\"."
# define EXIT_EMPTY 2
# define EXIT_ERROR 3

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

bool	is_double(char *s);
bool	parse_coords_format(char *s, t_color3 *point);

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

#endif