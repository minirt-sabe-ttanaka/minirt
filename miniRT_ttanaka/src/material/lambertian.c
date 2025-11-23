#include "material.h"

bool		lambertian_scatter(const void *object, const t_ray *r_in,
				const t_hit_record *rec, t_color3 *attenuation,
				t_ray *scattered);
t_material	create_lambertian(t_lambertian *l, t_color3 albedo);

bool	lambertian_scatter(const void *object, const t_ray *r_in,
		const t_hit_record *rec, t_color3 *attenuation, t_ray *scattered)
{
	const t_lambertian	*mat = (const t_lambertian *)object;
	t_vec3				scatter_dir;

	(void)r_in;
	scatter_dir = vec_add(rec->normal, random_unit_vector());
	if (vec_near_zero(scatter_dir))
		scatter_dir = rec->normal;
	*scattered = ray_init(vec_add(rec->p, vec_scale(rec->normal, SHADOW_BIAS)),
			scatter_dir);
	*attenuation = mat->albedo;
	return (true);
}

t_material	create_lambertian(t_lambertian *l, t_color3 albedo)
{
	static const t_material_vtable lambertian_vtable = {lambertian_scatter,
		material_default_emitted};
	t_material m;

	l->albedo = albedo;
	m.object = l;
	m.vtable = &lambertian_vtable;
	return (m);
}
