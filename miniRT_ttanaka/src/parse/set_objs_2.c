#include "parse.h"
static bool	parse_cylinder_config(char **splitted_data,
		t_cylinder_config *config, t_color3 *color);
bool	set_cylinder(char **splitted_data, t_scene *scene);

static bool	parse_cylinder_config(char **splitted_data,
		t_cylinder_config *config, t_color3 *color)
{
	if (ft_strarr_len(splitted_data) != 6)
		return (false);
	if (parse_coords_format(splitted_data[1], &(config->center)) == false)
		return (false);
	if (parse_coords_format(splitted_data[2], &(config->axis_dir)) == false)
		return (false);
	if (fabs(vec_norm_squared(config->axis_dir) - 1.0) > 1e-9)
		return (false);
	if (is_double(splitted_data[3]) == false
			|| is_double(splitted_data[4]) == false)
		return (false);
	config->radius = ft_strtod(splitted_data[3]) / 2.0;
	config->height = ft_strtod(splitted_data[4]);
	if (config->radius <= 0 || config->height <= 0)
		return (false);
	if (parse_color_format(splitted_data[5], color) == false)
		return (false);
	return (true);
}
bool	set_cylinder(char **splitted_data, t_scene *scene)
{
	t_cylinder_config	config;
	t_color3			color;
	t_cylinder			*cy;
	t_lambertian		*l;

	if (parse_cylinder_config(splitted_data, &config, &color) == false)
		return (false);
	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	l = (t_lambertian *)malloc(sizeof(t_lambertian));
	if (!cy || !l)
	{
		free(cy);
		free(l);
		return (false);
	}
	if (hittable_lst_add(scene->objects, create_cylinder(cy, &config,
				create_lambertian(l, color))) == false)
		return (false);
	return (true);
}
