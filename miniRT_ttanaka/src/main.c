#include "minirt.h"

static t_color3	calc_direct_light(t_scene *scene, t_hit_record *rec,
		t_color3 albedo)
{
	t_vec3			light_dir;
	double			dist;
	double			cos_theta;
	t_ray			shadow_ray;
	t_hit_record	tmp_rec;

	light_dir = vec_sub(scene->light.origin, rec->p);
	dist = vec_norm(light_dir);
	light_dir = vec_normalize(light_dir);
	shadow_ray = ray_init(vec_add(rec->p, vec_scale(rec->normal, SHADOW_BIAS)),
			light_dir);
	if (scene->bvh->vtable->hit(scene->bvh->object, &shadow_ray, SHADOW_BIAS,
			dist - SHADOW_BIAS, &tmp_rec))
		return (color_init(0, 0, 0));
	cos_theta = vec_dot(rec->normal, light_dir);
	if (cos_theta < 0)
		return (color_init(0, 0, 0));
	return (vec_scale(vec_mult(albedo, vec_scale(scene->light.color,
					scene->light.ratio)), cos_theta));
}

t_color3	ray_color(const t_ray *r, t_scene *scene, int depth)
{
	t_hit_record	rec;
	t_ray			scattered;
	t_color3		attenuation;
	t_color3		emitted;
	t_color3		direct_light;
	t_color3		indirect_light;

	if (depth <= 0)
		return (color_init(0, 0, 0));
	if (!scene->bvh->vtable->hit(scene->bvh->object, r, 0.001, 100000.0, &rec))
	{
		return (vec_scale(scene->ambient.color, scene->ambient.ratio));
	}
	emitted = rec.mat.vtable->emitted(rec.mat.object, 0, 0, &rec.p);
	if (!rec.mat.vtable->scatter(rec.mat.object, r, &rec, &attenuation,
			&scattered))
		return (emitted);
	direct_light = calc_direct_light(scene, &rec, attenuation);
	indirect_light = vec_mult(attenuation, ray_color(&scattered, scene, depth
				- 1));
	return (vec_add(emitted, vec_add(direct_light, indirect_light)));
}

int	raytracing(t_scene *scene, t_camera *cam)
{
	const int	max_depth = 10;
	const int	sample_per_pixel = 25;
	t_ray		r;
	t_color3	pixel_color;
	double		u;
	double		v;
	t_color3	corrected_color;
	double		progress;
	t_color3	sample_col;

	for (int y = 0; y < scene->screen_height; y++)
	{
		if (y % 10 == 0)
		{
			progress = (double)y / scene->screen_height * 100.0;
			printf("\rRendering... %.1f%%", progress);
			fflush(stdout);
		}
		for (int x = 0; x < scene->screen_width; x++)
		{
			pixel_color = color_init(0, 0, 0);
			for (int s = 0; s < sample_per_pixel; s++)
			{
				u = (x + random_double()) / (scene->screen_width - 1);
				v = (scene->screen_height - 1 - y + random_double())
					/ (scene->screen_height - 1);
				r = camera_get_ray(cam, u, v);
				sample_col = ray_color(&r, scene, max_depth);
				pixel_color = color_add(pixel_color, sample_col);
			}
			corrected_color.r = ft_clamp(sqrt(pixel_color.r / sample_per_pixel),
					0, 1);
			corrected_color.g = ft_clamp(sqrt(pixel_color.g / sample_per_pixel),
					0, 1);
			corrected_color.b = ft_clamp(sqrt(pixel_color.b / sample_per_pixel),
					0, 1);
			my_mlx_pixel_put(scene, x, y, tcolor2rgb(corrected_color));
		}
	}
	printf("\rRendering... 100.0%%\n");
	return (0);
}

static int	init_scene(t_scene *scene)
{
	scene->screen_width = 800;
	scene->screen_height = 450;
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, scene->screen_width,
			scene->screen_height, "miniRT");
	scene->img = mlx_new_image(scene->mlx, scene->screen_width,
			scene->screen_height);
	scene->addr = mlx_get_data_addr(scene->img, &scene->bits_per_pixel,
			&scene->line_length, &scene->endian);
	scene->ambient_initialized = false;
	scene->camera_initialized = false;
	scene->light_initialized = false;
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (init_scene(&scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_file(argv[1], &scene) == false)
		return (EXIT_FAILURE);
	raytracing(&scene, &(scene.camera));
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img, 0, 0);
	mlx_loop(scene.mlx);
	return (0);
}
