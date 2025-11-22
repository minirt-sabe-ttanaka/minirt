#include "shape.h"

bool		yz_rect_hit(const void *object, const t_ray *r, double t_min,
				double t_max, t_hit_record *rec);
t_hittable	create_yz_rect(t_yz_rect *rect, double y0, double y1, double z0,
				double z1, double k, t_material mat);

bool	yz_rect_hit(const void *object, const t_ray *r, double t_min, double t_max,
		t_hit_record *rec)
{
	const t_yz_rect	*rect = (const t_yz_rect *)object;
	double			t;
	double			y;
	double			z;
	t_vec3			outward_normal;

	t = (rect->k - r->orig.x) / r->dir.x;
	if (t < t_min || t > t_max)
		return (false);
	y = r->orig.y + t * r->dir.y;
	z = r->orig.z + t * r->dir.z;
	if (y < rect->y0 || y > rect->y1 || z < rect->z0 || z > rect->z1)
		return (false);
	rec->t = t;
	outward_normal = vec_init(1, 0, 0);
	set_face_normal(rec, r, &outward_normal);
	rec->mat = rect->mat;
	rec->p = ray_at(*r, t);
	return (true);
}

t_hittable	create_yz_rect(t_yz_rect *rect, double y0, double y1, double z0,
		double z1, double k, t_material mat)
{
	static const t_hittable_vtable	vtable = {yz_rect_hit};
	t_hittable						h;

	rect->y0 = y0;
	rect->y1 = y1;
	rect->z0 = z0;
	rect->z1 = z1;
	rect->k = k;
	rect->mat = mat;
	h.object = rect;
	h.vtable = &vtable;
	return (h);
}
