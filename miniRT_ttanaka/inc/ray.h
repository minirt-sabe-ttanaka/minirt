#ifndef RAY_H
#define RAY_H

#include "utils.h"

typedef struct s_ray
{
	t_point3				orig;
	t_vec3					dir;
}							t_ray;

t_ray						ray_init(t_point3 orig, t_vec3 dir);
t_point3					ray_at(t_ray ray, double t);

#endif