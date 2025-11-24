#ifndef BASE_HITTABLE_H
# define BASE_HITTABLE_H

# include "aabb.h"
# include "material.h"
# include "ray.h"
# include "utils.h"

typedef struct s_hittable_vtable
{
	bool					(*hit)(const void *object, const t_ray *r,
							t_double_range range, t_hit_record *rec);
	bool					(*bbox)(const void *object, t_aabb *output_bbox);
	void					(*destroy)(void *object);
}							t_hittable_vtable;

typedef struct s_hittable
{
	const void				*object;
	const t_hittable_vtable	*vtable;
}							t_hittable;

#endif