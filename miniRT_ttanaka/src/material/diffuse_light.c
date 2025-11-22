#include "material.h"

bool		diffuse_light_scatter(const void *object, const t_ray *r_in,
				const t_hit_record *rec, t_color3 *attenuation,
				t_ray *scattered);
t_color3	diffuse_light_emitted(const void *object, double u, double v,
				const t_point3 *p);
t_material	create_diffuse_light(t_diffuse_light *l, t_color3 emit_color);

bool	diffuse_light_scatter(const void *object, const t_ray *r_in,
		const t_hit_record *rec, t_color3 *attenuation, t_ray *scattered)
{
	(void)object;
	(void)r_in;
	(void)rec;
	(void)attenuation;
	(void)scattered;
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
			diffuse_light_emitted };
	t_material						m;

	l->emit_color = emit_color;
	m.object = l;
	m.vtable = &vtable;
	return (m);
}
