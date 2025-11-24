/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:23:10 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:23:11 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/material.h"

bool		lambertian_scatter(const void *object, t_scatter_ctx *ctx);
t_material	create_lambertian(t_lambertian *l, t_color3 albedo);

bool	lambertian_scatter(const void *object, t_scatter_ctx *ctx)
{
	const t_lambertian	*mat;
	t_vec3				scatter_dir;

	mat = (const t_lambertian *)object;
	scatter_dir = vec_add(ctx->rec->normal, random_unit_vector(ctx->seed));
	if (vec_near_zero(scatter_dir))
		scatter_dir = ctx->rec->normal;
	ctx->scattered = ray_init(vec_add(ctx->rec->p, vec_scale(ctx->rec->normal, SHADOW_BIAS)),
			scatter_dir);
	ctx->attenuation = mat->albedo;
	return (true);
}

t_material	create_lambertian(t_lambertian *l, t_color3 albedo)
{
	static const t_material_vtable lambertian_vtable = {lambertian_scatter,
		material_default_emitted, destroy_default_material };
	t_material m;

	l->albedo = albedo;
	m.object = l;
	m.vtable = &lambertian_vtable;
	return (m);
}
