#include "shape.h"

bool		zx_rect_hit(const void *object, const t_ray *r, double t_min,
				double t_max, t_hit_record *rec);
t_hittable	create_zx_rect(t_zx_rect *rect, double z0, double z1, double x0,
				double x1, double k, t_material mat);

bool	zx_rect_hit(const void *object, const t_ray *r, double t_min, double t_max,
		t_hit_record *rec)
{
	const t_zx_rect	*rect = (const t_zx_rect *)object;
	double			t;
	double			z;
	double			x;
	t_vec3			outward_normal;

	t = (rect->k - r->orig.y) / r->dir.y;
	if (t < t_min || t > t_max)
		return (false);
	z = r->orig.z + t * r->dir.z;
	x = r->orig.x + t * r->dir.x;
	if (z < rect->z0 || z > rect->z1 || x < rect->x0 || x > rect->x1)
		return (false);
	rec->t = t;
	outward_normal = vec_init(0, 1, 0);
	set_face_normal(rec, r, &outward_normal);
	rec->mat = rect->mat;
	rec->p = ray_at(*r, t);
	return (true);
}

t_hittable	create_zx_rect(t_zx_rect *rect, double z0, double z1, double x0,
		double x1, double k, t_material mat)
{
	static const t_hittable_vtable	vtable = {zx_rect_hit};
	t_hittable						h;

	rect->z0 = z0;
	rect->z1 = z1;
	rect->x0 = x0;
	rect->x1 = x1;
	rect->k = k;
	rect->mat = mat;
	h.object = rect;
	h.vtable = &vtable;
	return (h);
}
