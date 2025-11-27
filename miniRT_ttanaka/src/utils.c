#include "minirt.h"

void	set_face_normal(t_hit_record *rec, const t_ray *r,
		const t_vec3 *outward_normal)
{
	rec->front_face = vec_dot(r->dir, *outward_normal) < 0;
	if (rec->front_face)
		rec->normal = *outward_normal;
	else
		rec->normal = vec_scale(*outward_normal, -1);
}

