#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

double						ft_db_max(double x, double y);
double						ft_db_min(double x, double y);
double						ft_db_abs(double x);
void						ft_db_swap(double *x, double *y);

typedef struct s_vec3
{
	union
	{
		struct
		{
			double x, y, z;
		};
		struct
		{
			double r, g, b;
		};
	};
}							t_vec3;

typedef t_vec3				t_point3;
typedef t_vec3				t_color3;

t_vec3						vec_init(double x, double y, double z);
t_point3					point_init(double x, double y, double z);
t_vec3						vec_add(t_vec3 a, t_vec3 b);
t_vec3						vec_sub(t_vec3 a, t_vec3 b);
t_vec3						vec_mult(t_vec3 a, t_vec3 b);
t_vec3						vec_scale(t_vec3 v, double s);
double						vec_dot(t_vec3 a, t_vec3 b);
t_vec3						vec_cross(t_vec3 a, t_vec3 b);
double						vec_two_norm(t_vec3 v);
double						vec_norm(t_vec3 v);
t_vec3						vec_normalize(t_vec3 v);
bool						vec_near_zero(t_vec3 v);
t_vec3						vec_reflect(t_vec3 v, t_vec3 n);
t_vec3						vec_refract(t_vec3 uv, t_vec3 n,
								double etai_over_etat);
double						schlick(double cosine, double ref_idx);

typedef struct s_ray
{
	t_point3				orig;
	t_vec3					dir;
}							t_ray;

t_ray						ray_init(t_point3 orig, t_vec3 dir);
t_point3					ray_at(t_ray ray, double t);

int							ft_max(int x, int y);
int							ft_min(int x, int y);
int							ft_abs(int x);
void						ft_swap(int *x, int *y);

t_color3					color_init(double r, double g, double b);
t_color3					color_scale(t_color3 c, double s);
t_color3					color_add(t_color3 a, t_color3 b);
int							tcolor2rgb(t_color3 c);
int							create_rgb(int r, int g, int b);
int							get_r(int rgb);
int							get_g(int rgb);
int							get_b(int rgb);
int							add_shade(int rgb, double shade_factor);
int							get_opposite(int rgb);
int							interpolate_color(int c_start, int c_end, double t);

typedef struct s_camera
{
	t_point3				orig;
	t_point3				lower_left_corner;
	t_vec3					horizontal;
	t_vec3					vertical;
}							t_camera;

void						camera_init(t_camera *cam, t_point3 look_from,
								t_point3 look_at, t_vec3 vup, double vfov,
								double aspect_ratio);
t_ray						camera_get_ray(const t_camera *cam, double u,
								double v);

typedef struct s_world
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	int						screen_width;
	int						screen_height;
}							t_world;

void						my_mlx_pixel_put(t_world *world, int x, int y,
								int rgb);

struct s_hit_record;

typedef struct s_material_vtable
{
	bool					(*scatter)(const void *object, const t_ray *r_in,
							const struct s_hit_record *rec,
							t_color3 *attenuation, t_ray *scattered);
	t_color3				(*emitted)(const void *object, double u, double v,
						const t_point3 *p);
}							t_material_vtable;

typedef struct s_material
{
	const void				*object;
	const t_material_vtable	*vtable;
}							t_material;

t_color3					material_default_emitted(const void *object,
								double u, double v, const t_point3 *p);

typedef struct s_lambertian
{
	t_color3				albedo;
}							t_lambertian;

typedef struct s_metal
{
	t_color3				albedo;
	double					fuzz;
}							t_metal;

typedef struct s_dielectric
{
	double					ref_idx;
}							t_dielectric;

typedef struct s_diffuse_light
{
	t_color3				emit_color;
}							t_diffuse_light;

typedef struct s_hit_record
{
	t_point3				p;
	t_vec3					normal;
	t_material				mat;
	double					t;
	bool					front_face;
}							t_hit_record;

typedef struct s_hittable_vtable
{
	bool					(*hit)(const void *object, const t_ray *r,
							double t_min, double t_max, t_hit_record *rec);
}							t_hittable_vtable;

typedef struct s_hittable
{
	const void				*object;
	const t_hittable_vtable	*vtable;
}							t_hittable;

typedef struct s_hittable_lst
{
	t_hittable				*objects;
	int						size;
	int						capacity;
}							t_hittable_lst;

void						hittable_lst_init(t_hittable_lst *lst);
void						hittable_lst_free(t_hittable_lst *lst);
void						hittable_lst_add(t_hittable_lst *lst,
								t_hittable object);
bool						hittable_lst_hit(const void *object, const t_ray *r,
								double t_min, double t_max, t_hit_record *rec);
t_hittable					create_hittable_lst(t_hittable_lst *lst);

unsigned int				init_seed(void);
int							my_rand(void);
double						random_double(void);
double						random_double_range(double min, double max);
t_vec3						random_in_unit_sphere(void);
t_vec3						random_unit_vector(void);

bool						lambertian_scatter(const void *object,
								const t_ray *r_in, const t_hit_record *rec,
								t_color3 *attenuation, t_ray *scattered);
t_material					create_lambertian(t_lambertian *l, t_color3 albedo);
bool						metal_scatter(const void *object, const t_ray *r_in,
								const t_hit_record *rec, t_color3 *attenuation,
								t_ray *scattered);
t_material					create_metal(t_metal *metal, t_color3 albedo,
								double fuzz);
bool						dielectric_scatter(const void *object,
								const t_ray *r_in, const t_hit_record *rec,
								t_color3 *attenuation, t_ray *scattered);
t_material					create_dielectric(t_dielectric *d, double ref_idx);

bool						diffuse_light_scatter(const void *object,
								const t_ray *r_in, const t_hit_record *rec,
								t_color3 *attenuation, t_ray *scattered);
t_color3					diffuse_light_emitted(const void *object, double u,
								double v, const t_point3 *p);
t_material					create_diffuse_light(t_diffuse_light *l,
								t_color3 emit_color);

void						set_face_normal(t_hit_record *rec, const t_ray *r,
								const t_vec3 *outward_normal);

typedef struct s_sphere
{
	t_point3				center;
	double					radius;
	t_material				mat;
}							t_sphere;

t_hittable					create_sphere(t_sphere *s, t_point3 center,
								double radius, t_material mat);
bool						sphere_hit(const void *object, const t_ray *r,
								double t_min, double t_max, t_hit_record *rec);

typedef struct s_xy_rect
{
	double					x0;
	double					x1;
	double					y0;
	double					y1;
	double					k;
	t_material				mat;
}							t_xy_rect;

typedef struct s_yz_rect
{
	double					y0;
	double					y1;
	double					z0;
	double					z1;
	double					k;
	t_material				mat;
}							t_yz_rect;
typedef struct s_zx_rect
{
	double					z0;
	double					z1;
	double					x0;
	double					x1;
	double					k;
	t_material				mat;
}							t_zx_rect;

bool		xy_rect_hit(const void *object, const t_ray *r, double t_min,
				double t_max, t_hit_record *rec);
t_hittable	create_xy_rect(t_xy_rect *rect, double x0, double x1, double y0,
				double y1, double k, t_material mat);

bool		yz_rect_hit(const void *object, const t_ray *r, double t_min,
				double t_max, t_hit_record *rec);
t_hittable	create_yz_rect(t_yz_rect *rect, double y0, double y1, double z0,
				double z1, double k, t_material mat);

bool		zx_rect_hit(const void *object, const t_ray *r, double t_min,
				double t_max, t_hit_record *rec);
t_hittable	create_zx_rect(t_zx_rect *rect, double z0, double z1, double x0,
				double x1, double k, t_material mat);

#endif