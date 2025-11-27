/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:23:10 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 15:10:44 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/material.h"

bool		lambertian_scatter(const void *object, const t_scatter_ctx *in,
				t_scatter_record *out);
t_material	create_lambertian(t_lambertian *l, t_color3 albedo);
double		lambertian_scattering_pdf(const void *obj, const t_ray *r_in,
				const t_hit_record *rec, const t_ray *scattered);

bool	lambertian_scatter(const void *object, const t_scatter_ctx *in,
		t_scatter_record *out)
{
	const t_lambertian	*mat;

	mat = (const t_lambertian *)object;
	out->is_specular = false;
	out->attenuation = mat->albedo;
	out->pdf_ptr = create_cosine_pdf(in->rec->normal);
	return (true);
}

t_material	create_lambertian(t_lambertian *l, t_color3 albedo)
{
	static const t_material_vtable	lambertian_vtable = {lambertian_scatter,
			lambertian_scattering_pdf, material_default_emitted,
			destroy_default_material};
	t_material						m;

	l->albedo = albedo;
	m.object = l;
	m.vtable = &lambertian_vtable;
	return (m);
}

double	lambertian_scattering_pdf(const void *obj, const t_ray *r_in,
		const t_hit_record *rec, const t_ray *scattered)
{
	double	cosine;

	(void)obj;
	(void)r_in;
	cosine = vec_dot(rec->normal, vec_normalize(scattered->dir));
	if (cosine < 0)
		return (0.0);
	return (cosine / M_PI);
}
