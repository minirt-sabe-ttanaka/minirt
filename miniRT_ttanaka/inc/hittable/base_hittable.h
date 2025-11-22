#ifndef BASE_HITTABLE_H
# define BASE_HITTABLE_H

# include "aabb.h"
# include "material.h"
# include "ray.h"

typedef struct s_hittable_vtable
{
	bool					(*hit)(const void *object, const t_ray *r,
							double t_min, double t_max, t_hit_record *rec);
	bool					(*bbox)(const void *object, t_aabb *output_bbox);
}							t_hittable_vtable;

typedef struct s_hittable
{
	const void				*object;
	const t_hittable_vtable	*vtable;
}							t_hittable;

#endif