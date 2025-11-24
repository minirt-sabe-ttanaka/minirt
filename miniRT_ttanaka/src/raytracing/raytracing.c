#include "raytracing.h"

int	raytracing(t_scene *scene, t_camera *cam)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	t_renderer		renderer;
	int				i;

	renderer.scene = scene;
	renderer.cam = cam;
	renderer.next_y = 0;
	if (pthread_mutex_init(&renderer.update_mutex, NULL))
		return (EXIT_FAILURE);
	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].id = i;
		thread_data[i].renderer = &renderer;
		if (pthread_create(&threads[i], NULL, render_thread, &thread_data[i]))
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
		pthread_join(threads[i++], NULL);
	pthread_mutex_destroy(&renderer.update_mutex);
	return (EXIT_SUCCESS);
}
