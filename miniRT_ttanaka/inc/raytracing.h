#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "hittable.h"
# include "plot.h"
# include "scene.h"
# include "utils.h"
# include <pthread.h>
# define BAR_WIDTH 50
# define MAX_DEPTH 10
# define SAMPLE_PER_PIXEL 30
# define NUM_THREADS 8

int					raytracing(t_scene *scene, t_camera *cam);

void				display_progress_bar(int current, int total);
t_color3			calc_direct_light(t_scene *scene, t_hit_record *rec,
						t_color3 albedo);
t_color3	ray_color(const t_ray *r, t_scene *scene, int depth, unsigned int *seed);
t_color3			sampling_ray(t_scene *scene, t_camera *cam, int x, int y, unsigned int *seed);

typedef struct s_renderer
{
	t_scene			*scene;
	t_camera		*cam;
	int				next_y;
	pthread_mutex_t	update_mutex;
}					t_renderer;

typedef struct s_thread_data
{
	t_renderer		*renderer;
	int				id;
}					t_thread_data;

int					take_new_line(t_renderer *r);
void				*render_thread(void *arg);

#endif