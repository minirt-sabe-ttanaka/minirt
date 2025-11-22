#include "material.h"

bool metal_scatter(const void *object, const t_ray *r_in, const t_hit_record *rec, t_color3 *attenuation, t_ray *scattered);
t_material create_metal(t_metal *metal, t_color3 albedo, double fuzz);

bool metal_scatter(const void *object, const t_ray *r_in, const t_hit_record *rec, t_color3 *attenuation, t_ray *scattered)
{
    const t_metal *mat = (const t_metal*)object;
    t_vec3 reflected_dir;
    t_vec3 fuzzed_dir;

    reflected_dir = vec_reflect(vec_normalize(r_in->dir), rec->normal);
    fuzzed_dir = vec_add(reflected_dir, vec_scale(random_in_unit_sphere(), mat->fuzz));
    *scattered = ray_init(rec->p, fuzzed_dir);
    *attenuation = mat->albedo;

    return (vec_dot(scattered->dir, rec->normal) > 0);
}

t_material create_metal(t_metal *metal, t_color3 albedo, double fuzz)
{
    static const t_material_vtable metal_vtable = { metal_scatter, material_default_emitted };
    t_material m;

    metal->albedo = albedo;
    metal->fuzz = fmin(fuzz, 1);
    m.object = metal;
    m.vtable = &metal_vtable;
    return (m);
}
