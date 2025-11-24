#ifndef AABB_H
# define AABB_H

# include "ray.h"
# include "utils.h"
# include <float.h>

typedef struct s_aabb
{
	t_vec3	min;
	t_vec3	max;
}			t_aabb;

bool		aabb_hit(const t_aabb *bbox, const t_ray *r, t_double_range range);
t_aabb		merge_bbox(const t_aabb *bbox_0, const t_aabb *bbox_1);
t_vec3		calc_centroid_of_bbox(const t_aabb *bbox);
double		calc_surface_area_of_bbox(const t_aabb *bbox);
void		init_aabb(t_aabb *aabb);
void		set_axis_aabb(t_aabb *box, t_vec3 p1, t_vec3 p2);

#endif