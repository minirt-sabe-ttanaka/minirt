#include "material.h"

bool		dielectric_scatter(const void *object, const t_ray *r_in,
				const t_hit_record *rec, t_color3 *attenuation,
				t_ray *scattered);
t_material	create_dielectric(t_dielectric *d, double ref_idx);

bool	dielectric_scatter(const void *object, const t_ray *r_in,
		const t_hit_record *rec, t_color3 *attenuation, t_ray *scattered)
{
	const t_dielectric	*mat = (const t_dielectric *)object;
	double				etai_over_etat;
	t_vec3				unit_dir;
	double				cos_theta;
	double				sin_theta;
	double				reflect_prob;

	*attenuation = color_init(1.0, 1.0, 1.0);
	if (rec->front_face)
		etai_over_etat = 1.0 / mat->ref_idx;
	else
		etai_over_etat = mat->ref_idx;
	unit_dir = vec_normalize(r_in->dir);
	cos_theta = fmin(vec_dot(vec_scale(unit_dir, -1), rec->normal), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	if (etai_over_etat * sin_theta > 1.0)
	{
		*scattered = ray_init(rec->p, vec_reflect(unit_dir, rec->normal));
		return (true);
	}
	reflect_prob = schlick(cos_theta, etai_over_etat);
	if (random_double() < reflect_prob)
	{
		*scattered = ray_init(rec->p, vec_reflect(unit_dir, rec->normal));
		return (true);
	}
	*scattered = ray_init(rec->p, vec_refract(unit_dir, rec->normal,
				etai_over_etat));
	return (true);
}

t_material	create_dielectric(t_dielectric *d, double ref_idx)
{
	static const t_material_vtable dielectric_vtable = {dielectric_scatter, material_default_emitted};
	t_material m;

	d->ref_idx = ref_idx;
	m.object = d;
	m.vtable = &dielectric_vtable;
	return (m);
}
