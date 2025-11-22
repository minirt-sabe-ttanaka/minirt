#include "camera.h"

void			camera_init(t_camera *cam, t_camera_config *config);
t_ray			camera_get_ray(const t_camera *cam, double u, double v);

static double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

void	camera_init(t_camera *cam, t_camera_config *config)
{
	double	theta;
	double	half_width;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;

	theta = degrees_to_radians(config->fov);
	half_width = tan(theta / 2.0);
	w = vec_scale(vec_normalize(config->look_to), -1.0);
	u = vec_normalize(vec_cross(config->vup, w));
	v = vec_cross(w, u);
	cam->orig = config->look_from;
	cam->horizontal = vec_scale(u, 2.0 * half_width);
	cam->vertical = vec_scale(v, 2.0 * half_width / config->aspect_ratio);
	cam->lower_left_corner = vec_sub(vec_sub(vec_sub(cam->orig,
					vec_scale(cam->horizontal, 0.5)), vec_scale(cam->vertical,
					0.5)), w);
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