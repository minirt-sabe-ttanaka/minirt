#ifndef MINIRT_H
# define MINIRT_H

# include "camera.h"
# include "hittable.h"
# include "material.h"
# include "mlx.h"
# include "parse.h"
# include "ray.h"
# include "raytracing.h"
# include "scene.h"
# include "shape.h"
# include "utils.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define EPS 1e-2
# define SHADOW_BIAS 1e-2

void	my_mlx_pixel_put(t_scene *world, int x, int y, int rgb);

#endif