/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:08:59 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 23:31:03 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/hittable/shape.h"

t_hittable	create_triangle(t_triangle *s, t_triangle_config *t_config,
				t_material mat);
bool		triangle_hit(const void *object, const t_ray *r,
				t_double_range range, t_hit_record *rec);
bool		triangle_bbox(const void *object, t_aabb *output_bbox);

t_hittable	create_triangle(t_triangle *s, t_triangle_config *t_config,
		t_material mat)
{
	static const t_hittable_vtable	triangle_vtable = {triangle_hit,
			triangle_bbox, triangle_destroy, triangle_pdf_value,
			triangle_random};
	t_hittable						h;

	s->p0 = t_config->p0;
	s->p1 = t_config->p1;
	s->p2 = t_config->p2;
	s->mat = mat;
	h.object = s;
	h.vtable = &triangle_vtable;
	return (h);
}

static bool	calc_and_validate_tuv(const t_triangle *tr, const t_ray *r,
		double *tuv, t_double_range range)
{
	t_vec3	d;
	t_vec3	e1;
	t_vec3	e2;
	t_vec3	f;
	double	denominator_inv;

	d = r->dir;
	e1 = vec_sub(tr->p1, tr->p0);
	e2 = vec_sub(tr->p2, tr->p0);
	f = vec_sub(r->orig, tr->p0);
	if (fabs(vec_dot(vec_cross(d, e2), e1)) < 1e-6)
		return (false);
	denominator_inv = 1 / vec_dot(vec_cross(d, e2), e1);
	tuv[0] = denominator_inv * vec_dot(vec_cross(f, e1), e2);
	if (tuv[0] < range.min || range.max < tuv[0])
		return (false);
	tuv[1] = denominator_inv * vec_dot(vec_cross(d, e2), f);
	tuv[2] = denominator_inv * vec_dot(vec_cross(f, e1), d);
	return (tuv[1] >= 0 && tuv[2] >= 0 && tuv[1] + tuv[2] <= 1);
}

bool	triangle_hit(const void *object, const t_ray *r, t_double_range range,
		t_hit_record *rec)
{
	const t_triangle	*tr;
	double				tuv[3];
	t_vec3				outward_normal;

	tr = (const t_triangle *)object;
	if (calc_and_validate_tuv(tr, r, tuv, range) == false)
		return (false);
	rec->mat = tr->mat;
	rec->t = tuv[0];
	rec->p = ray_at(*r, rec->t);
	outward_normal = vec_normalize(vec_cross(vec_sub(tr->p1, tr->p0),
				vec_sub(tr->p2, tr->p0)));
	set_face_normal(rec, r, &outward_normal);
	return (true);
}

bool	triangle_bbox(const void *object, t_aabb *output_bbox)
{
	const t_triangle	*tr;
	static const double	padding = 1e-4;

	tr = (const t_triangle *)object;
	output_bbox->max = tr->p0;
	output_bbox->min = tr->p0;
	update_aabb(output_bbox, tr->p1);
	update_aabb(output_bbox, tr->p2);
	if (fabs(output_bbox->max.x - output_bbox->min.x) < padding)
		output_bbox->max.x += padding;
	if (fabs(output_bbox->max.y - output_bbox->min.y) < padding)
		output_bbox->max.y += padding;
	if (fabs(output_bbox->max.z - output_bbox->min.z) < padding)
		output_bbox->max.z += padding;
	return (true);
}
