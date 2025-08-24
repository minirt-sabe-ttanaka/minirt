#include "minirt.h"

t_color3	ray_color(const t_ray *r, const t_color3 *background,
		const t_hittable *world, int depth)
{
	t_hit_record	rec;
	t_ray			scattered;
	t_color3		attenuation;
	t_color3		emitted;

	if (depth <= 0)
		return (color_init(0, 0, 0));
	if (!world->vtable->hit(world->object, r, 0.001, 100000, &rec))
		return (*background);
	emitted = rec.mat.vtable->emitted(rec.mat.object, 0, 0, &rec.p);
	if (!rec.mat.vtable->scatter(rec.mat.object, r, &rec, &attenuation,
			&scattered))
		return (emitted);
	return (vec_add(emitted, vec_mult(attenuation, ray_color(&scattered,
					background, world, depth - 1))));
}

int	raytracing(t_world *world_struct, t_hittable *world, t_camera *cam,
		const t_color3 *background)
{
	const int	max_depth = 10;
	const int	sample_per_pixel = 10;
	t_ray		r;
	t_color3	pixel_color;
	double		u;
	double		v;
			t_color3 corrected_color;

	for (int y = 0; y < world_struct->screen_height; y++)
	{
		for (int x = 0; x < world_struct->screen_width; x++)
		{
			pixel_color = color_init(0, 0, 0);
			for (int s = 0; s < sample_per_pixel; s++)
			{
				u = (x + random_double()) / (world_struct->screen_width - 1);
				v = (world_struct->screen_height - 1 - y + random_double())
					/ (world_struct->screen_height - 1);
				r = camera_get_ray(cam, u, v);
				pixel_color = color_add(pixel_color, ray_color(&r, background,
							world, max_depth));
			}
			corrected_color.r = sqrt(pixel_color.r / sample_per_pixel);
			corrected_color.g = sqrt(pixel_color.g / sample_per_pixel);
			corrected_color.b = sqrt(pixel_color.b / sample_per_pixel);
			my_mlx_pixel_put(world_struct, x, y, tcolor2rgb(corrected_color));
		}
	}
	return (0);
}

int	main(void)
{
	t_camera		cam;
	t_world			world_struct;
	const t_color3	background = color_init(1, 1, 1);
	t_hittable_lst	cornel_box;
	t_hittable		world;
	t_sphere		pink_sphere;
	t_sphere 		green_sphere;
	t_sphere		blue_sphere;
	t_sphere 		white_sphere;
	t_lambertian	pink;
	t_lambertian	green;
	t_metal			blue;
	t_dielectric	white;
	t_material		mat_pink;
	t_material		mat_green;
	t_material		mat_blue;
	t_material		mat_white;

	world_struct.screen_height = 540;
	world_struct.screen_width = 960;
	world_struct.mlx = mlx_init();
	world_struct.win = mlx_new_window(world_struct.mlx,
			world_struct.screen_width, world_struct.screen_height, "miniRT");
	world_struct.img = mlx_new_image(world_struct.mlx,
			world_struct.screen_width, world_struct.screen_height);
	world_struct.addr = mlx_get_data_addr(world_struct.img,
			&(world_struct.bits_per_pixel), &(world_struct.line_length),
			&(world_struct.endian));
	camera_init(&cam, point_init(0, 0, 0), point_init(0, 0, -1),
		point_init(0, 1, 0), 40, (double)world_struct.screen_width
		/ world_struct.screen_height);
	mat_pink = create_lambertian(&pink, color_init(0.8, 0.3, 0.3));
	mat_green = create_lambertian(&green, color_init(0.8, 0.8, 0.0));
	mat_blue = create_metal(&blue, color_init(0.2, 0.2, 0.8), 0.0);
	mat_white = create_dielectric(&white, 1.5);
	hittable_lst_init(&cornel_box);
	hittable_lst_add(&cornel_box, create_sphere(&pink_sphere, vec_init(0, 0, -1), 0.5, mat_pink));
	hittable_lst_add(&cornel_box, create_sphere(&green_sphere, vec_init(0, -100.5, -1), 100, mat_green));
	hittable_lst_add(&cornel_box, create_sphere(&blue_sphere, vec_init(1, 0, -1), 0.5, mat_blue));
	hittable_lst_add(&cornel_box, create_sphere(&white_sphere, vec_init(-1, 0, -1), 0.5, mat_white));
	world = create_hittable_lst(&cornel_box);
	raytracing(&world_struct, &world, &cam, &background);
	mlx_put_image_to_window(world_struct.mlx, world_struct.win,
		world_struct.img, 0, 0);
	mlx_loop(world_struct.mlx);
}
