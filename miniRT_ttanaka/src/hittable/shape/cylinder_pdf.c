/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_pdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 02:24:10 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 15:38:44 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/hittable/shape.h"

t_vec3			cylinder_random(const void *object, const t_point3 o,
					unsigned int *seed);
double			cylinder_pdf_value(const void *object, const t_point3 o,
					const t_vec3 v);

static double	get_cylinder_area(const t_cylinder *cy)
{
	return (2.0 * M_PI * cy->radius * cy->height);
}

t_vec3	cylinder_random(const void *object, const t_point3 o,
		unsigned int *seed)
{
	const t_cylinder	*cy;
	t_onb				uvw;
	double				r1;
	double				r2;
	t_point3			rand_point_local;

	cy = (const t_cylinder *)object;
	onb_build_from_w(&uvw, cy->axis_dir);
	r1 = random_double_range(seed, -cy->height / 2.0, cy->height / 2.0);
	r2 = random_double_range(seed, 0, 2.0 * M_PI);
	rand_point_local = vec_add(vec_scale(uvw.u, cy->radius * cos(r2)),
			vec_scale(uvw.v, cy->radius * sin(r2)));
	rand_point_local = vec_add(rand_point_local, vec_scale(uvw.w, r1));
	return (vec_sub(vec_add(cy->center, rand_point_local), o));
}

double	cylinder_pdf_value(const void *object, const t_point3 o, const t_vec3 v)
{
	const t_cylinder *cy = (const t_cylinder *)object;
	t_hit_record rec;
	t_ray ray;
	double area;
	double dist_sq;
	double cosine;

	ray = ray_init(o, v);
	if (!cylinder_hit(cy, &ray, (t_double_range){0.001, INFINITY}, &rec))
		return (0.0);
	dist_sq = rec.t * rec.t * vec_norm_squared(ray.dir);
	area = get_cylinder_area(cy);
	cosine = fabs(vec_dot(ray.dir, rec.normal));
	if (cosine < 1e-6)
		return (0.0);
	return (dist_sq / (area * cosine));
}