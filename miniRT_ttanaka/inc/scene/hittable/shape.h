/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:34 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:16:20 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "core/utils.h"
# include "scene/hittable.h"
# include "scene/material.h"
# include "struct.h"

# define BBOX_INF 1e30

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	t_material	mat;
}				t_sphere;

typedef struct s_sphere_config
{
	t_point3	center;
	double		radius;
}				t_sphere_config;

t_hittable		create_sphere(t_sphere *s, t_point3 center, double radius,
					t_material mat);
bool			sphere_hit(const void *object, const t_ray *r,
					t_double_range range, t_hit_record *rec);

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
	t_material	mat;
}				t_plane;

typedef struct t_plane_config
{
	t_point3	point;
	t_vec3		normal;
}				t_plane_config;

t_hittable		create_plane(t_plane *p, t_point3 point, t_vec3 normal,
					t_material mat);
bool			plane_hit(const void *object, const t_ray *r,
					t_double_range range, t_hit_record *rec);

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis_dir;
	double		radius;
	double		height;
	t_material	mat;
}				t_cylinder;

typedef struct s_cylinder_config
{
	t_point3	center;
	t_vec3		axis_dir;
	double		radius;
	double		height;
}				t_cylinder_config;

t_hittable		create_cylinder(t_cylinder *cy, t_cylinder_config *config,
					t_material mat);
bool			cylinder_hit(const void *object, const t_ray *r,
					t_double_range range, t_hit_record *rec);

void			cylinder_destroy(void *object);
void			plane_destroy(void *object);
void			sphere_destroy(void *object);

#endif