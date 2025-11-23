#ifndef SHAPE_H
# define SHAPE_H

# include "hittable.h"
# include "material.h"
# include "util.h"

# define BBOX_INF 1e30

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	t_material	mat;
}				t_sphere;

typedef struct s_sphere_config
{
	t_point3	center;
	double		radius;
}				t_sphere_config;

t_hittable		create_sphere(t_sphere *s, t_point3 center, double radius,
					t_material mat);
bool			sphere_hit(const void *object, const t_ray *r, double t_min,
					double t_max, t_hit_record *rec);

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
	t_material	mat;
}				t_plane;

typedef struct t_plane_config
{
	t_point3	point;
	t_vec3		normal;
}				t_plane_config;

t_hittable		create_plane(t_plane *p, t_point3 point, t_vec3 normal,
					t_material mat);
bool			plane_hit(const void *object, const t_ray *r, double t_min,
					double t_max, t_hit_record *rec);

typedef struct s_xy_rect
{
	double		x0;
	double		x1;
	double		y0;
	double		y1;
	double		k;
	t_material	mat;
}				t_xy_rect;

typedef struct s_yz_rect
{
	double		y0;
	double		y1;
	double		z0;
	double		z1;
	double		k;
	t_material	mat;
}				t_yz_rect;
typedef struct s_zx_rect
{
	double		z0;
	double		z1;
	double		x0;
	double		x1;
	double		k;
	t_material	mat;
}				t_zx_rect;

bool			xy_rect_hit(const void *object, const t_ray *r, double t_min,
					double t_max, t_hit_record *rec);
t_hittable		create_xy_rect(t_xy_rect *rect, double x0, double x1, double y0,
					double y1, double k, t_material mat);

bool			yz_rect_hit(const void *object, const t_ray *r, double t_min,
					double t_max, t_hit_record *rec);
t_hittable		create_yz_rect(t_yz_rect *rect, double y0, double y1, double z0,
					double z1, double k, t_material mat);

bool			zx_rect_hit(const void *object, const t_ray *r, double t_min,
					double t_max, t_hit_record *rec);
t_hittable		create_zx_rect(t_zx_rect *rect, double z0, double z1, double x0,
					double x1, double k, t_material mat);

bool			zx_rect_hit(const void *object, const t_ray *r, double t_min,
					double t_max, t_hit_record *rec);
t_hittable		create_zx_rect(t_zx_rect *rect, double z0, double z1, double x0,
					double x1, double k, t_material mat);

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis_dir;
	double		radius;
	double		height;
	t_material	mat;
}				t_cylinder;

typedef struct s_cylinder_config
{
	t_point3	center;
	t_vec3		axis_dir;
	double		radius;
	double		height;
}				t_cylinder_config;

t_hittable		create_cylinder(t_cylinder *cy, t_cylinder_config *config,
					t_material mat);
bool			cylinder_hit(const void *object, const t_ray *r, double t_min,
					double t_max, t_hit_record *rec);

#endif