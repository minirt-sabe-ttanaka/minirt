#include "minirt.h"

static int	init_scene(t_scene *scene)
{
	scene->screen_width = WIDTH;
	scene->screen_height = HEIGHT;
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
