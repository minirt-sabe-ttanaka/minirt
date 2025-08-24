#include "minirt.h"

void			camera_init(t_camera *cam, t_point3 look_from, t_point3 look_at,
					t_vec3 vup, double vfov, double aspect_ratio);
t_ray			camera_get_ray(const t_camera *cam, double u, double v);

static double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

void	camera_init(t_camera *cam, t_point3 look_from, t_point3 look_at,
		t_vec3 vup, double vfov, double aspect_ratio)
{
	double	theta;
	double	h;
	double	viewpoint_height;
	double	viewpoint_width;
	t_vec3	u, v, w;

	theta = degrees_to_radians(vfov);
	h = tan(theta / 2.0);
	viewpoint_height = 2.0 * h;
	viewpoint_width = aspect_ratio * viewpoint_height;

    w = vec_normalize(vec_sub(look_from, look_at));
    u = vec_normalize(vec_cross(vup, w));
    v = vec_cross(w, u);

	cam->orig = look_from;
	cam->horizontal = vec_scale(u, viewpoint_width);
	cam->vertical = vec_scale(v, viewpoint_height);
	cam->lower_left_corner = vec_sub(vec_sub(vec_sub(cam->orig, vec_scale(cam->horizontal, 0.5)), vec_scale(cam->vertical, 0.5)), w);
}

t_ray	camera_get_ray(const t_camera *cam, double u, double v)
{
	t_point3 target;
	t_vec3 dir;

	target = vec_add(cam->lower_left_corner, vec_scale(cam->horizontal, u));
	target = vec_add(target, vec_scale(cam->vertical, v));
	dir = vec_sub(target, cam->orig);
	return (ray_init(cam->orig, dir));
}