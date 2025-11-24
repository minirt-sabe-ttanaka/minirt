/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:36 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:15:53 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "core/ray.h"
# include "core/utils.h"
# include "engine/camera.h"
# include "engine/parse.h"
# include "engine/raytracing.h"
# include "engine/scene.h"
# include "mlx.h"
# include "scene/hittable.h"
# include "scene/hittable/shape.h"
# include "scene/material.h"
# include "struct.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define WIDTH 800
# define HEIGHT 800
# define EPS 1e-2
# define SHADOW_BIAS 1e-2

void	my_mlx_pixel_put(t_scene *world, int x, int y, int rgb);

#endif