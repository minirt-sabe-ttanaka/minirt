/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:23:57 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 15:28:39 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/hittable/shape.h"

t_hittable	create_sphere(t_sphere *s, t_point3 center, double radius,
				t_material mat);
bool		sphere_hit(const void *object, const t_ray *r, t_double_range range,
				t_hit_record *rec);
bool		sphere_bbox(const void *object, t_aabb *output_bbox);

t_hittable	create_sphere(t_sphere *s, t_point3 center, double radius,
		t_material mat)
{
	static const t_hittable_vtable	sphere_vtable = {sphere_hit, sphere_bbox,
			sphere_destroy, sphere_pdf_value, sphere_random};
	t_hittable						h;

	s->center = center;
	s->radius = radius;
	s->mat = mat;
	h.object = s;
	h.vtable = &sphere_vtable;
	return (h);
}

static void	calc_sp_coefficients(const t_sphere *sp, const t_ray *r,
		double *eqn)
{
	t_vec3	co;

	co = vec_sub(r->orig, sp->center);
	eqn[0] = vec_norm_squared(r->dir);
	eqn[1] = 2.0 * vec_dot(co, r->dir);
	eqn[2] = vec_norm_squared(co) - sp->radius * sp->radius;
}

bool	sphere_hit(const void *object, const t_ray *r, t_double_range range,
		t_hit_record *rec)
{
	const t_sphere	*sp;
	double			eqn[3];
	double			roots[2];
	int				i;
	t_vec3			outward_normal;

	sp = (const t_sphere *)object;
	calc_sp_coefficients(sp, r, eqn);
	if (ft_solve_quadratic_equation(eqn[0], eqn[1], eqn[2], roots) == false)
		return (false);
	i = -1;
	while (++i < 2)
	{
		if (roots[i] < range.min || range.max < roots[i])
			continue ;
		rec->t = roots[i];
		rec->p = ray_at(*r, roots[i]);
		outward_normal = vec_scale(vec_sub(rec->p, sp->center), 1.0
				/ sp->radius);
		set_face_normal(rec, r, &outward_normal);
		rec->mat = sp->mat;
		return (true);
	}
	return (false);
}

bool	sphere_bbox(const void *object, t_aabb *output_bbox)
{
	const t_sphere	*sp;

	sp = (const t_sphere *)object;
	output_bbox->min = vec_sub(sp->center, vec_init(sp->radius, sp->radius,
				sp->radius));
	output_bbox->max = vec_add(sp->center, vec_init(sp->radius, sp->radius,
				sp->radius));
	return (true);
}
