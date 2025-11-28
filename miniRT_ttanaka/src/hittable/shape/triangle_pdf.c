#include "scene/hittable/shape.h"

double			triangle_pdf_value(const void *object, const t_point3 o,
					const t_vec3 v);
t_vec3			triangle_random(const void *object, const t_point3 o,
					unsigned int *seed);

static double	calc_triangle_area(const t_triangle *tr)
{
	t_vec3	e1;
	t_vec3	e2;

	e1 = vec_sub(tr->p1, tr->p0);
	e2 = vec_sub(tr->p2, tr->p0);
	return (vec_norm(vec_cross(e1, e2)) * 0.5);
}

double	triangle_pdf_value(const void *object, const t_point3 o, const t_vec3 v)
{
	const t_triangle	*tr;
	t_hit_record		rec;
	t_ray				ray;
	double				dist_sq;
	double				cosine;

	tr = (const t_triangle *)object;
	ray = ray_init(o, v);
	if (!triangle_hit(tr, &ray, (t_double_range){0.001, INFINITY}, &rec))
		return (0.0);
	dist_sq = rec.t * rec.t * vec_norm_squared(ray.dir);
	cosine = fabs(vec_dot(ray.dir, rec.normal));
	if (cosine < 1e-6)
		return (0.0);
	return (dist_sq / (calc_triangle_area(tr) * cosine));
}

t_vec3	triangle_random(const void *obj, const t_point3 o, unsigned int *seed)
{
	const t_triangle	*tr = (const t_triangle *)obj;
	double				min;
	double				max;
	double				tmp;
	t_vec3				p;

	min = random_double(seed);
	max = random_double(seed);
	if (max < min)
	{
		tmp = min;
		min = max;
		max = tmp;
	}
	p = vec_add(vec_add(vec_scale(tr->p0, min), vec_scale(tr->p1, 1.0 - max)),
			vec_scale(tr->p2, max - min));
	return (vec_sub(p, o));
}
