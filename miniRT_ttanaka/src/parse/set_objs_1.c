#include "parse.h"

static bool	parse_sphere_config(char **splitted_data, t_sphere_config *s_config, t_material_config *m_config);
bool		set_sphere(char **splitted_data, t_scene *scene);
static bool	parse_plane_config(char **splitted_data, t_plane_config *p_config, t_material_config *m_config);
bool		set_plane(char **splitted_data, t_scene *scene);

static bool	parse_sphere_config(char **splitted_data, t_sphere_config *s_config,
		t_material_config *m_config)
{
	size_t	len;

	len = ft_strarr_len(splitted_data);
	if (len != 5 && len != 6)
		return (false);
	if (parse_coords_format(splitted_data[1], &(s_config->center)) == false)
		return (false);
	if (parse_double(splitted_data[2], &(s_config->radius)) == false)
		return (false);
	if (s_config->radius <= 0.0)
		return (false);
	s_config->radius /= 2.0;
	if (parse_material_format(splitted_data[3], splitted_data[4],
			splitted_data[5], m_config) == false)
		return (false);
	return (true);
}

bool	set_sphere(char **splitted_data, t_scene *scene)
{
	t_sphere			*sphere;
	t_sphere_config		s_config;
	t_material_config	m_config;
	t_material			m;

	if (parse_sphere_config(splitted_data, &s_config, &m_config) == false)
		return (false);
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (false);
	if (create_material(&m_config, &m) == false)
	{
		free(sphere);
		return (false);
	}
	if (hittable_lst_add(scene->objects, create_sphere(sphere, s_config.center,
				s_config.radius, m)) == false)
	{
		free(sphere);
		return (false);
	}
	return (true);
}

static bool	parse_plane_config(char **splitted_data, t_plane_config *p_config, t_material_config *m_config)
{
	size_t len;

	len = ft_strarr_len(splitted_data);
	if (len != 5 && len != 6)
		return (false);
	if (parse_coords_format(splitted_data[1], &(p_config->point)) == false)
		return (false);
	if (parse_coords_format(splitted_data[2], &(p_config->normal)) == false)
		return (false);
	if (fabs(vec_norm_squared(p_config->normal) - 1.0) > EPS)
		return (false);
	if (parse_material_format(splitted_data[3], splitted_data[4], splitted_data[5], m_config) == false)
		return (false);
	return (true);
}

bool	set_plane(char **splitted_data, t_scene *scene)
{
	t_plane				*plane;
	t_plane_config		p_config;
	t_material_config	m_config;
	t_material			m;

	if (parse_plane_config(splitted_data, &p_config, &m_config) == false)
		return (false);
	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (false);
	if (create_material(&m_config, &m) == false)
	{
		free(plane);
		return (false);
	}
	if (hittable_lst_add(scene->objects, create_plane(plane, p_config.point, p_config.normal, m)) == false)
	{
		free(plane);
		return (false);
	}
	return (true);
}
