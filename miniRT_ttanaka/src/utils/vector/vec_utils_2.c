#include "utils/vector.h"

double	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
double	vec_norm_squared(t_vec3 v);
double	vec_norm(t_vec3 v);
t_vec3	vec_normalize(t_vec3 v);

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

double	vec_norm_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vec_norm(t_vec3 v)
{
	return (sqrt(vec_norm_squared(v)));
}

t_vec3	vec_normalize(t_vec3 v)
{
	double	norm;

	norm = vec_norm(v);
	if (norm == 0)
		return (v);
	return (vec_init(v.x / norm, v.y / norm, v.z / norm));
}
