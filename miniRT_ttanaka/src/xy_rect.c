#include "minirt.h"

bool		xy_rect_hit(const void *object, const t_ray *r, double t_min,
				double t_max, t_hit_record *rec);
t_hittable	create_xy_rect(t_xy_rect *rect, double x0, double x1, double y0,
				double y1, double k, t_material mat);

bool	xy_rect_hit(const void *object, const t_ray *r, double t_min, double t_max,
		t_hit_record *rec)
{
	const t_xy_rect	*rect = (const t_xy_rect *)object;
	double			t;
	double			x;
	double			y;
	t_vec3			outward_normal;

	t = (rect->k - r->orig.z) / r->dir.z;
	if (t < t_min || t > t_max)
		return (false);
	x = r->orig.x + t * r->dir.x;
	y = r->orig.y + t * r->dir.y;
	if (x < rect->x0 || x > rect->x1 || y < rect->y0 || y > rect->y1)
		return (false);
	rec->t = t;
	outward_normal = vec_init(0, 0, 1);
	set_face_normal(rec, r, &outward_normal);
	rec->mat = rect->mat;
	rec->p = ray_at(*r, t);
	return (true);
}

t_hittable	create_xy_rect(t_xy_rect *rect, double x0, double x1, double y0,
		double y1, double k, t_material mat)
{
	static const t_hittable_vtable	vtable = {xy_rect_hit};
	t_hittable						h;

	rect->x0 = x0;
	rect->x1 = x1;
	rect->y0 = y0;
	rect->y1 = y1;
	rect->k = k;
	rect->mat = mat;
	h.object = rect;
	h.vtable = &vtable;
	return (h);
}
