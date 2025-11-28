/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objs_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:36 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 23:22:27 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/parse.h"

static bool	parse_cylinder_config(char **splitted_data,
				t_cylinder_config *c_config, t_material_config *m_config);
bool		set_cylinder(char **splitted_data, t_scene *scene);
static bool	parse_triangle_config(char **splitted_data,
				t_triangle_config *tr_config, t_material_config *m_config);
bool		set_triangle(char **splitted_data, t_scene *scene);

static bool	parse_cylinder_config(char **splitted_data,
		t_cylinder_config *c_config, t_material_config *m_config)
{
	size_t	len;

	len = ft_strarr_len(splitted_data);
	if (len != 7 && len != 8)
		return (false);
	if (parse_coords_format(splitted_data[1], &(c_config->center)) == false)
		return (false);
	if (parse_coords_format(splitted_data[2], &(c_config->axis_dir)) == false)
		return (false);
	if (fabs(vec_norm_squared(c_config->axis_dir) - 1.0) > EPS)
		return (false);
	if (parse_double(splitted_data[3], &(c_config->radius)) == false
		|| parse_double(splitted_data[4], &(c_config->height)) == false)
		return (false);
	if (c_config->radius <= 0 || c_config->height <= 0)
		return (false);
	c_config->radius /= 2.0;
	if (parse_material_format(splitted_data[5], splitted_data[6],
			splitted_data[7], m_config) == false)
		return (false);
	return (true);
}

bool	set_cylinder(char **splitted_data, t_scene *scene)
{
	t_cylinder			*cy;
	t_cylinder_config	c_config;
	t_material_config	m_config;
	t_material			m;

	if (parse_cylinder_config(splitted_data, &c_config, &m_config) == false)
		return (false);
	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (false);
	if (create_material(&m_config, &m) == false)
	{
		free(cy);
		return (false);
	}
	if (hittable_lst_add(scene->objects, create_cylinder(cy, &c_config,
				m)) == false)
	{
		free(cy);
		return (false);
	}
	if (m_config.type == diffuse_light
		&& hittable_lst_add((t_hittable_lst *)scene->light_group.object,
			create_cylinder(cy, &c_config, m)) == false)
	{
		free(cy);
		return (false);
	}
	return (true);
}

static bool	parse_triangle_config(char **splitted_data,
		t_triangle_config *tr_config, t_material_config *m_config)
{
	size_t	len;

	len = ft_strarr_len(splitted_data);
	if (len != 6 && len != 7)
		return (false);
	if (parse_coords_format(splitted_data[1], &(tr_config->p0)) == false)
		return (false);
	if (parse_coords_format(splitted_data[2], &(tr_config->p1)) == false)
		return (false);
	if (parse_coords_format(splitted_data[3], &(tr_config->p2)) == false)
		return (false);
	if (vec_norm_squared(vec_cross(vec_sub(tr_config->p1, tr_config->p0),
				vec_sub(tr_config->p2, tr_config->p0))) < EPS)
		return (false);
	if (parse_material_format(splitted_data[4], splitted_data[5],
			splitted_data[6], m_config) == false)
		return (false);
	return (true);
}

bool	set_triangle(char **splitted_data, t_scene *scene)
{
	t_triangle			*tr;
	t_triangle_config	tr_config;
	t_material_config	m_config;
	t_material			m;

	if (parse_triangle_config(splitted_data, &tr_config, &m_config) == false)
		return (false);
	tr = (t_triangle *)malloc(sizeof(t_triangle));
	if (!tr)
		return (false);
	if (create_material(&m_config, &m) == false)
	{
		free(tr);
		return (false);
	}
	if (hittable_lst_add(scene->objects, create_triangle(tr, &tr_config,
				m)) == false)
	{
		free(tr);
		return (false);
	}
	if (m_config.type == diffuse_light
		&& hittable_lst_add((t_hittable_lst *)scene->light_group.object,
			create_triangle(tr, &tr_config, m)) == false)
	{
		free(tr);
		return (false);
	}
	return (true);
}
