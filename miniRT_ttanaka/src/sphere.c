#include "minirt.h"

t_hittable	create_sphere(t_sphere *s, t_point3 center, double radius,
				t_material mat);
bool		sphere_hit(const void *object, const t_ray *r, double t_min,
				double t_max, t_hit_record *rec);



t_hittable	create_sphere(t_sphere *s, t_point3 center, double radius,
		t_material mat)
{
	static const t_hittable_vtable	sphere_vtable = {sphere_hit};
	t_hittable						h;

	s->center = center;
	s->radius = radius;
	s->mat = mat;
	h.object = s;
	h.vtable = &sphere_vtable;
	return (h);
}

bool	sphere_hit(const void *object, const t_ray *r, double t_min,
		double t_max, t_hit_record *rec)
{
	const t_sphere *s = (const t_sphere *)object;
	t_vec3 oc = vec_sub(r->orig, s->center);

	double a = vec_two_norm(r->dir);
	double half_b = vec_dot(oc, r->dir);
	double c = vec_two_norm(oc) - s->radius * s->radius;
	double d = half_b * half_b - a * c;
	if (d < 0)
		return (false);
	double root = (-half_b - sqrt(d)) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrt(d)) / a;
		if (root < t_min || t_max < root)
			return (false);
	}
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	t_vec3 outward_normal = vec_scale(vec_sub(rec->p, s->center), 1.0
			/ s->radius);
    set_face_normal(rec, r, &outward_normal);
    rec->mat = s->mat;
	return (true);
}
