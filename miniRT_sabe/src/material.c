/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesouichirou <abesouichirou@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:44:29 by abesouichir       #+#    #+#             */
/*   Updated: 2025/08/22 14:56:51 by abesouichir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_material *material_new(const void *object, const t_material_vtable *vtable)
{
    t_material *mat = ft_calloc(1, sizeof(t_material));
    if (!mat)
        return (NULL);
    mat->object = object;
    mat->vtable = vtable;
    return (mat);
}

bool material_scatter(const void *object, const t_ray *r_in,
                       const t_hit_record *rec, t_color3 *attenuation, t_ray *scattered)
{
  (void)r_in; // r_in は使用しない
  t_vec3 scattered_dir = vec3_add(rec->normal, vec3_random_in_unit_sphere());
  scattered->origin = rec->p;
  scattered->dir = scattered_dir;
  const t_lambertian *lambertian = (const t_lambertian *)object;
  *attenuation = lambertian->albedo;
  return (true);
}

t_material *lambertian_new(t_color3 albedo)
{
    t_lambertian *lambertian = ft_calloc(1, sizeof(t_lambertian));
    if (!lambertian)
        return (NULL);
    lambertian->albedo = albedo;
    static const t_material_vtable lambertian_vtable = { .scatter = material_scatter };
    return material_new(lambertian, &lambertian_vtable);
}

bool metal_scatter(const void *object, const t_ray *r_in,
                       const t_hit_record *rec, t_color3 *attenuation, t_ray *scattered)
{
    (void)r_in; // r_in は使用しない
    t_vec3 reflected = vec3_reflect(unit_vector(r_in->dir), rec->normal);
    scattered->origin = rec->p;
    scattered->dir = vec3_add(reflected, vec3_mul_s(vec3_random_in_unit_sphere(), ((const t_metal *)object)->fuzz));
    const t_metal *metal = (const t_metal *)object;
    *attenuation = metal->albedo;
    return (vec3_dot(scattered->dir, rec->normal) > 0);
}

t_material *metal_new(t_color3 albedo, double fuzz)
{
    t_metal *metal = ft_calloc(1, sizeof(t_metal));
    if (!metal)
        return (NULL);
    metal->albedo = albedo;
    if (fuzz > 1.0)
        fuzz = 1.0; // 粗さは 0.0 以上 1.0 以下に制限
    else if (fuzz < 0.0)
        fuzz = 0.0;
    metal->fuzz = fuzz;
    static const t_material_vtable metal_vtable = { .scatter = metal_scatter };
    return material_new(metal, &metal_vtable);
}

bool dieletric_scatter(const void *object, const t_ray *r_in,
                       const t_hit_record *rec, t_color3 *attenuation, t_ray *scattered)
{
    *attenuation = ((t_dielectric *)object)->albedo;
    double eta_ratio = rec->front_face ? (1.0 / ((t_dielectric *)object)->ref_idx) : ((t_dielectric *)object)->ref_idx;
    t_vec3 unit_dir = unit_vector(r_in->dir);
    double cos_theta = vec3_dot(vec3_neg(unit_dir), rec->normal);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    if (eta_ratio * sin_theta > 1.0) {
        // 全反射
        t_vec3 reflected = vec3_reflect(unit_dir, rec->normal);
        scattered->origin = rec->p;
        scattered->dir = reflected;
        return true;
    }
    // 屈折
    double reflect_prob = schlick(cos_theta, eta_ratio);
    if (rand_double(0.0, 1.0) < reflect_prob) {
        t_vec3 reflected = vec3_reflect(unit_dir, rec->normal);
        scattered->origin = rec->p;
        scattered->dir = reflected;
        return true;
    }
    t_vec3 refracted = refract(unit_dir, rec->normal, eta_ratio);
    scattered->origin = rec->p;
    scattered->dir = refracted;
    return true;
}

t_material *dielectric_new(t_color3 albedo, double ref_idx)
{
    t_dielectric *dielectric = ft_calloc(1, sizeof(t_dielectric));
    if (!dielectric)
        return (NULL);
    dielectric->albedo = albedo;
    dielectric->ref_idx = ref_idx;
    static const t_material_vtable dielectric_vtable = { .scatter = dieletric_scatter };
    return material_new(dielectric, &dielectric_vtable);
}