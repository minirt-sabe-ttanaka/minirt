/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:23:42 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 15:28:11 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/hittable/shape.h"

t_hittable	create_plane(t_plane *p, t_point3 point, t_vec3 normal,
				t_material mat);
bool		plane_hit(const void *object, const t_ray *r, t_double_range range,
				t_hit_record *rec);
bool		plane_bbox(const void *object, t_aabb *output_bbox);

t_hittable	create_plane(t_plane *p, t_point3 point, t_vec3 normal,
		t_material mat)
{
	static const t_hittable_vtable	plane_vtable = {plane_hit, plane_bbox,
			plane_destroy, plane_pdf_value, plane_random};
	t_hittable						h;

	p->point = point;
	p->normal = normal;
	p->mat = mat;
	h.object = p;
	h.vtable = &plane_vtable;
	return (h);
}

bool	plane_hit(const void *object, const t_ray *r, t_double_range range,
		t_hit_record *rec)
{
	const t_plane	*p;
	double			t;
	double			dot_d_n;
	t_vec3			outward_normal;

	p = (const t_plane *)object;
	dot_d_n = vec_dot(r->dir, p->normal);
	if (fabs(dot_d_n) < 1e-6)
		return (false);
	t = vec_dot(vec_sub(p->point, r->orig), p->normal) / dot_d_n;
	if (t < range.min || range.max < t)
		return (false);
	rec->t = t;
	rec->p = ray_at(*r, t);
	outward_normal = p->normal;
	set_face_normal(rec, r, &outward_normal);
	rec->mat = p->mat;
	return (true);
}

bool	plane_bbox(const void *object, t_aabb *output_bbox)
{
	const t_plane	*pl;

	pl = (const t_plane *)object;
	output_bbox->min = vec_sub(pl->point, vec_init(BBOX_INF, BBOX_INF,
				BBOX_INF));
	output_bbox->max = vec_add(pl->point, vec_init(BBOX_INF, BBOX_INF,
				BBOX_INF));
	return (true);
}
