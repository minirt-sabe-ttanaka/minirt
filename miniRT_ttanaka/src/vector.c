#include "minirt.h"

t_vec3		vec_init(double x, double y, double z);
t_point3	point_init(double x, double y, double z);
t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_mult(t_vec3 a, t_vec3 b);
t_vec3		vec_scale(t_vec3 v, double s);
double		vec_dot(t_vec3 a, t_vec3 b);
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
double		vec_two_norm(t_vec3 v);
double		vec_norm(t_vec3 v);
t_vec3		vec_normalize(t_vec3 v);
bool		vec_near_zero(t_vec3 v);
t_vec3		vec_reflect(t_vec3 v, t_vec3 n);
t_vec3		vec_refract(t_vec3 uv, t_vec3 n, double etai_over_etat);
double		schlick(double cosine, double ref_idx);

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

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return (vec_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return (vec_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec_mult(t_vec3 a, t_vec3 b)
{
	return (vec_init(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3	vec_scale(t_vec3 v, double s)
{
	return (vec_init(v.x * s, v.y * s, v.z * s));
}
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

double	vec_two_norm(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vec_norm(t_vec3 v)
{
	return (sqrt(vec_two_norm(v)));
}

t_vec3	vec_normalize(t_vec3 v)
{
	double	norm;

	norm = vec_norm(v);
	if (norm == 0)
		return (v);
	return (vec_init(v.x / norm, v.y / norm, v.z / norm));
}

bool	vec_near_zero(t_vec3 v)
{
	const double	eps = 1e-8;

	if (fabs(v.x) < eps && fabs(v.y) < eps && fabs(v.z) < eps)
		return (true);
	return (false);
}

t_vec3	vec_reflect(t_vec3 v, t_vec3 n)
{
	double	dot_vn;
	t_vec3	scaled_n;

	dot_vn = vec_dot(v, n);
	scaled_n = vec_scale(n, 2 * dot_vn);
	return (vec_sub(v, scaled_n));
}

t_vec3	vec_refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = fmin(vec_dot(vec_scale(uv, -1), n), 1.0);
	r_out_perp = vec_scale(vec_add(uv, vec_scale(n, cos_theta)),
			etai_over_etat);
	r_out_parallel = vec_scale(n, -sqrt(fabs(1.0 - vec_two_norm(r_out_perp))));
	return (vec_add(r_out_perp, r_out_parallel));
}

double	schlick(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}
