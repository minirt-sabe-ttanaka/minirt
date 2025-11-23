#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "hittable.h"
# include "plot.h"
# include "scene.h"
# include "utils.h"

# define BAR_WIDTH 50
# define MAX_DEPTH 10
# define SAMPLE_PER_PIXEL 30

int	raytracing(t_scene *scene, t_camera *cam);

#endif