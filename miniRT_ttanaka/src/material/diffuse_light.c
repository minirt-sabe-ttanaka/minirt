/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:23:08 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/26 11:35:44 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/material.h"

bool		diffuse_light_scatter(const void *object, const t_scatter_ctx *in,
				t_scatter_record *out);
t_color3	diffuse_light_emitted(const void *object, double u, double v,
				const t_point3 *p);
t_material	create_diffuse_light(t_diffuse_light *l, t_color3 emit_color);

bool	diffuse_light_scatter(const void *object, const t_scatter_ctx *in,
		t_scatter_record *out)
{
	(void)object;
	(void)in;
	(void)out;
	return (false);
}

t_color3	diffuse_light_emitted(const void *object, double u, double v,
		const t_point3 *p)
{
	(void)u;
	(void)v;
	(void)p;
	return (((const t_diffuse_light *)object)->emit_color);
}

t_material	create_diffuse_light(t_diffuse_light *l, t_color3 emit_color)
{
	static const t_material_vtable	vtable = {diffuse_light_scatter,
			dummy_scattering_pdf, diffuse_light_emitted,
			destroy_default_material};
	t_material						m;

	l->emit_color = emit_color;
	m.object = l;
	m.vtable = &vtable;
	return (m);
}
