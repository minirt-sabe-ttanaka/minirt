/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesouichirou <abesouichirou@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 09:40:57 by abesouichir       #+#    #+#             */
/*   Updated: 2025/08/22 11:10:12 by abesouichir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void sphere_create(t_hittable_lst *lst, t_vec3 center, double radius, t_material mat) {
    static const t_hittable_vtable sphere_vtable = { .hit = hit_sphere };
    t_sphere *sphere = malloc(sizeof(t_sphere));
    if (!sphere) {
        perror("Failed to allocate memory for sphere");
        return;
    }
    sphere->center = center;
    sphere->radius = radius;
    sphere->mat = mat;
    hittable_lst_push(lst, (void *)sphere, &sphere_vtable);
}

bool hit_sphere(const void *object, const t_ray *r, double t_min, double t_max, t_hit_record *rec) {
  const t_sphere *sphere = (const t_sphere *)object;
  t_vec3 oc = vec3_sub(r->origin, sphere->center);
  double a = vec3_length2(r->dir);
  double b = vec3_dot(oc, r->dir);
  double c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
  double discriminant = b * b - a * c;
  if (discriminant > 0)
  {
    double root = sqrt(discriminant);
    double temp = (-b - root) / a;
    if (temp < t_max && temp > t_min)
    {
      rec->t = temp;
      rec->p = ray_at(*r, rec->t);
      t_vec3 outward_normal = vec3_div_s(vec3_sub(rec->p, sphere->center), sphere->radius);
      set_face_normal(rec, r, outward_normal);
      rec->mat = sphere->mat;
      return true;
    }
    temp = (-b + root) / a;
    if (temp < t_max && temp > t_min)
    {
      rec->t = temp;
      rec->p = ray_at(*r, rec->t);
      t_vec3 outward_normal = vec3_div_s(vec3_sub(rec->p, sphere->center), sphere->radius);
      set_face_normal(rec, r, outward_normal);
      rec->mat = sphere->mat;
      return true;
    }
  }
  return false;
}