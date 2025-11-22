#include "parse.h"

static bool	parse_sphere_config(char **splitted_data, t_point3 *center,
				double *radius, t_color3 *color);
bool		set_sphere(char **splitted_data, t_scene *scene);
static bool	parse_plane_config(char **splitted_data, t_point3 *point,
				t_vec3 *normal, t_color3 *color);
bool		set_plane(char **splitted_data, t_scene *scene);

static bool	parse_sphere_config(char **splitted_data, t_point3 *center,
		double *radius, t_color3 *color)
{
	double	diameter;

	if (ft_strarr_len(splitted_data) != 4)
		return (false);
	if (parse_coords_format(splitted_data[1], center) == false)
		return (false);
	if (is_double(splitted_data[2]) == false)
		return (false);
	diameter = ft_strtod(splitted_data[2]);
	if (diameter <= 0.0)
		return (false);
	*radius = diameter / 2.0;
	if (parse_color_format(splitted_data[3], color) == false)
		return (false);
	return (true);
}

bool	set_sphere(char **splitted_data, t_scene *scene)
{
	t_sphere		*sphere;
	t_lambertian	*l;
	t_point3		center;
	t_color3		color;
	double			radius;

	if (parse_sphere_config(splitted_data, &center, &radius, &color) == false)
		return (false);
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	l = (t_lambertian *)malloc(sizeof(t_lambertian));
	if (!sphere || !l)
	{
		free(sphere);
		free(l);
		return (false);
	}
	if (hittable_lst_add(scene->objects, create_sphere(sphere, center, radius,
				create_lambertian(l, color))) == false)
		return (false);
	return (true);
}

static bool	parse_plane_config(char **splitted_data, t_point3 *point,
		t_vec3 *normal, t_color3 *color)
{
	if (ft_strarr_len(splitted_data) != 4)
		return (false);
	if (parse_coords_format(splitted_data[1], point) == false)
		return (false);
	if (parse_coords_format(splitted_data[2], normal) == false)
		return (false);
	if (fabs(vec_norm_squared(*normal) - 1.0) > 1e-9)
		return (false);
	if (parse_color_format(splitted_data[3], color) == false)
		return (false);
	return (true);
}
bool	set_plane(char **splitted_data, t_scene *scene)
{
	t_point3		point;
	t_vec3			normal;
	t_color3		color;
	t_plane			*plane;
	t_lambertian	*l;

	if (parse_plane_config(splitted_data, &point, &normal, &color) == false)
		return (false);
	plane = (t_plane *)malloc(sizeof(t_plane));
	l = (t_lambertian *)malloc(sizeof(t_lambertian));
	if (!plane || !l)
	{
		free(plane);
		free(l);
		return (false);
	}
	if (hittable_lst_add(scene->objects, create_plane(plane, point, normal,
				create_lambertian(l, color))) == false)
		return (false);
	return (true);
}
