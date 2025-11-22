#include "../../inc/minirt.h"

t_ray	ray_init(t_point3 orig, t_vec3 dir)
{
	t_ray	r;

	r.orig = orig;
	r.dir = dir;
	return (r);
}

t_point3	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.orig, vec_scale(ray.dir, t)));
}