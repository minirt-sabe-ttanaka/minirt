/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:23:12 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/26 11:35:32 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/material.h"

bool		metal_scatter(const void *object, const t_scatter_ctx *in,
				t_scatter_record *out);
t_material	create_metal(t_metal *metal, t_color3 albedo, double fuzz);

bool	metal_scatter(const void *object, const t_scatter_ctx *in,
		t_scatter_record *out)
{
	const t_metal	*mat = (const t_metal *)object;
	t_vec3			reflected;
	t_vec3			fuzzed_dir;

	out->is_specular = true;
	out->attenuation = mat->albedo;
	out->pdf_ptr = NULL;
	reflected = vec_reflect(vec_normalize(in->r_in->dir), in->rec->normal);
	fuzzed_dir = vec_add(reflected,
			vec_scale(random_in_unit_sphere(in->seed), mat->fuzz));
	out->specular_ray = ray_init(vec_add(in->rec->p, vec_scale(in->rec->normal, SHADOW_BIAS)), fuzzed_dir);
	return (vec_dot(out->specular_ray.dir, in->rec->normal) > 0);
}

t_material	create_metal(t_metal *metal, t_color3 albedo, double fuzz)
{
	static const t_material_vtable	metal_vtable = {metal_scatter,
			dummy_scattering_pdf, material_default_emitted, destroy_default_material};
	t_material						m;

	metal->albedo = albedo;
	metal->fuzz = fmin(fuzz, 1);
	m.object = metal;
	m.vtable = &metal_vtable;
	return (m);
}
