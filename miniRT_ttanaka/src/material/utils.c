#include "scene/material.h"

t_color3	material_default_emitted(const void *object, double u, double v,
		const t_point3 *p);
double	dummy_scattering_pdf(const void *obj, const t_ray *r_in,
		const t_hit_record *rec, const t_ray *scattered);

t_color3	material_default_emitted(const void *object, double u, double v,
		const t_point3 *p)
{
	(void)object;
	(void)u;
	(void)v;
	(void)p;
	return (color_init(0, 0, 0));
}

double	dummy_scattering_pdf(const void *obj, const t_ray *r_in,
		const t_hit_record *rec, const t_ray *scattered)
{
	(void)obj;
	(void)r_in;
	(void)rec;
	(void)scattered;
	return (0.0);
}
