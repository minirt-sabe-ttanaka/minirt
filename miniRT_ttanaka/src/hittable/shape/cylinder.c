/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:17:40 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:17:40 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/hittable/shape.h"

bool		cylinder_hit(const void *object, const t_ray *r,
				t_double_range range, t_hit_record *rec);
t_hittable	create_cylinder(t_cylinder *cy, t_cylinder_config *config,
				t_material mat);
bool		cylinder_bbox(const void *object, t_aabb *output_bbox);

t_hittable	create_cylinder(t_cylinder *cy, t_cylinder_config *config,
		t_material mat)
{
	static const t_hittable_vtable	cylinder_vtable = {cylinder_hit,
			cylinder_bbox, cylinder_destroy};
	t_hittable						h;

	cy->center = config->center;
	cy->axis_dir = config->axis_dir;
	cy->radius = config->radius;
	cy->height = config->height;
	cy->mat = mat;
	h.object = cy;
	h.vtable = &cylinder_vtable;
	return (h);
}

static void	calc_cy_coefficients(const t_cylinder *cy, const t_ray *r,
		double *eqn)
{
	t_vec3	co;

	co = vec_sub(r->orig, cy->center);
	eqn[0] = vec_norm_squared(r->dir) - pow(vec_dot(r->dir, cy->axis_dir), 2);
	eqn[1] = 2.0 * (vec_dot(r->dir, co) - vec_dot(r->dir, cy->axis_dir)
			* vec_dot(co, cy->axis_dir));
	eqn[2] = vec_norm_squared(co) - pow(vec_dot(co, cy->axis_dir), 2)
		- cy->radius * cy->radius;
}

static void	get_cylinder_normal(t_hit_record *rec, const t_cylinder *cy,
		const t_ray *r)
{
	t_point3	h;
	t_vec3		hp;
	t_vec3		outward_normal;

	h = vec_add(cy->center, vec_scale(cy->axis_dir, vec_dot(vec_sub(rec->p,
						cy->center), cy->axis_dir)));
	hp = vec_sub(rec->p, h);
	outward_normal = vec_normalize(hp);
	set_face_normal(rec, r, &outward_normal);
}

bool	cylinder_hit(const void *object, const t_ray *r, t_double_range range,
		t_hit_record *rec)
{
	const t_cylinder	*cy = (const t_cylinder *)object;
	double				roots[2];
	double				coefficients[3];
	int					i;

	calc_cy_coefficients(cy, r, coefficients);
	if (ft_solve_quadratic_equation(coefficients[0], coefficients[1],
			coefficients[2], roots) == false)
		return (false);
	i = -1;
	while (++i < 2)
	{
		if (roots[i] < range.min || range.max < roots[i])
			continue ;
		if (fabs(vec_dot(vec_sub(ray_at(*r, roots[i]), cy->center),
					cy->axis_dir)) <= cy->height / 2)
		{
			rec->t = roots[i];
			rec->p = ray_at(*r, roots[i]);
			get_cylinder_normal(rec, cy, r);
			rec->mat = cy->mat;
			return (true);
		}
	}
	return (false);
}

bool	cylinder_bbox(const void *object, t_aabb *output_bbox)
{
	const t_cylinder	*cy = (t_cylinder *)object;
	t_vec3				half_axis;
	t_vec3				top;
	t_vec3				bottom;
	t_aabb				axis_box;

	half_axis = vec_scale(cy->axis_dir, cy->height / 2.0);
	top = vec_add(cy->center, half_axis);
	bottom = vec_sub(cy->center, half_axis);
	set_axis_aabb(&axis_box, top, bottom);
	output_bbox->min = vec_sub(axis_box.min, vec_init(cy->radius, cy->radius,
				cy->radius));
	output_bbox->max = vec_add(axis_box.max, vec_init(cy->radius, cy->radius,
				cy->radius));
	return (true);
}
