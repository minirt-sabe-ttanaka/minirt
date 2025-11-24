/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:01:12 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:01:13 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
#define RAY_H

#include "utils.h"

typedef struct s_ray
{
	t_point3				orig;
	t_vec3					dir;
}							t_ray;

t_ray						ray_init(t_point3 orig, t_vec3 dir);
t_point3					ray_at(t_ray ray, double t);

#endif