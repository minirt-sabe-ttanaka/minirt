#include "utils/vector.h"

t_vec3		vec_init(double x, double y, double z);
t_point3	point_init(double x, double y, double z);

t_vec3	vec_init(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_point3	point_init(double x, double y, double z)
{
	return (vec_init(x, y, z));
}
