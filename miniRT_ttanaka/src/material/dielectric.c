/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dielectric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:23:06 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/26 11:35:52 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/material.h"

bool		dielectric_scatter(const void *object, const t_scatter_ctx *in,
				t_scatter_record *out);
t_material	create_dielectric(t_dielectric *d, double ref_idx);

static bool	should_reflect(double ratio, double cos_theta, unsigned int *seed)
{
	double	sin_theta;
	double	prob;

	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	if (ratio * sin_theta > 1.0)
		return (true);
	prob = schlick(cos_theta, ratio);
	if (random_double(seed) < prob)
		return (true);
	return (false);
}

bool	dielectric_scatter(const void *object, const t_scatter_ctx *in,
		t_scatter_record *out)
{
	const t_dielectric	*mat;
	double				ratio;
	t_vec3				unit_dir;
	double				cos_theta;
	t_vec3				dir;

	mat = (const t_dielectric *)object;
	out->is_specular = true;
	out->attenuation = color_init(1.0, 1.0, 1.0);
	out->pdf_ptr = NULL;
	unit_dir = vec_normalize(in->r_in->dir);
	ratio = mat->ref_idx;
	if (in->rec->front_face)
		ratio = 1.0 / mat->ref_idx;
	cos_theta = fmin(vec_dot(vec_scale(unit_dir, -1), in->rec->normal), 1.0);
	if (should_reflect(ratio, cos_theta, in->seed))
		dir = vec_reflect(unit_dir, in->rec->normal);
	else
		dir = vec_refract(unit_dir, in->rec->normal, ratio);
	out->specular_ray = ray_init(in->rec->p, dir);
	return (true);
}

t_material	create_dielectric(t_dielectric *d, double ref_idx)
{
	static const t_material_vtable	dielectric_vtable = {dielectric_scatter,
			dummy_scattering_pdf, material_default_emitted,
			destroy_default_material};
	t_material						m;

	d->ref_idx = ref_idx;
	m.object = d;
	m.vtable = &dielectric_vtable;
	return (m);
}
