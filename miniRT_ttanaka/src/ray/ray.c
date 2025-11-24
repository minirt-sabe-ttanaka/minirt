/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:21:34 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:21:35 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/ray.h"

t_ray	ray_init(t_point3 orig, t_vec3 dir)
{
	t_ray	r;

	r.orig = orig;
	r.dir = dir;
	return (r);
}

t_point3	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.orig, vec_scale(ray.dir, t)));
}