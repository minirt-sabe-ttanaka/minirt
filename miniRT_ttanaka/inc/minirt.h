#ifndef MINIRT_H
# define MINIRT_H

# include "utils.h"
# include "mlx.h"
# include "ray.h"
# include "camera.h"
# include "hittable.h"
# include "material.h"
# include "scene.h"
# include "shape.h"
# include "parse.h"

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

void	my_mlx_pixel_put(t_scene *world, int x, int y, int rgb);

#endif