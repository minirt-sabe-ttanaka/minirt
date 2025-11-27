#include "scene/hittable/shape.h"

double			sphere_pdf_value(const void *object, const t_point3 o,
					const t_vec3 v);
t_vec3			sphere_random(const void *object, const t_point3 o,
					unsigned int *seed);

static t_vec3	random_to_sphere(double radius, double dist_squared,
		unsigned int *seed)
{
	double	r1;
	double	r2;
	double	z;
	double	phi;
	double	cos_theta_max;
	double	sin_theta;

	r1 = random_double(seed);
	r2 = random_double(seed);
	cos_theta_max = sqrt(1.0 - (radius * radius) / dist_squared);
	z = 1.0 + r2 * (cos_theta_max - 1.0);
	sin_theta = sqrt(1.0 - z * z);
	phi = 2.0 * M_PI * r1;
	return (vec_init(cos(phi) * sin_theta, sin(phi) * sin_theta, z));
}

double	sphere_pdf_value(const void *object, const t_point3 o, const t_vec3 v)
{
	const t_sphere	*sp = (const t_sphere *)object;
	t_hit_record	rec;
	t_ray			ray;
	double			cos_theta_max;
	double			solid_angle;
	double			dist_squared;

	ray = ray_init(o, v);
	if (!sphere_hit(sp, &ray, (t_double_range){0.001, INFINITY}, &rec))
		return (0.0);
	dist_squared = vec_norm_squared(vec_sub(sp->center, o));
	cos_theta_max = sqrt(1.0 - (sp->radius * sp->radius) / dist_squared);
	solid_angle = 2.0 * M_PI * (1.0 - cos_theta_max);
	return (1.0 / solid_angle);
}

t_vec3	sphere_random(const void *object, const t_point3 o, unsigned int *seed)
{
	const t_sphere *sp = (const t_sphere *)object;
	t_vec3 direction;
	double dist_squared;
	t_onb uvw;
	t_vec3 local_dir;

	direction = vec_sub(sp->center, o);
	dist_squared = vec_norm_squared(direction);
	onb_build_from_w(&uvw, direction);
	local_dir = random_to_sphere(sp->radius, dist_squared, seed);
	return (onb_local2world(&uvw, local_dir.x, local_dir.y, local_dir.z));
}