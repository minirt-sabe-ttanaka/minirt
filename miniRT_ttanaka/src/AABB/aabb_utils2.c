/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:59:59 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:00:00 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/aabb.h"

void init_aabb(t_aabb *aabb)
{
    aabb->min = vec_init(INFINITY, INFINITY, INFINITY);
    aabb->max = vec_init(-INFINITY, -INFINITY, -INFINITY);
}

void	set_axis_aabb(t_aabb *box, t_vec3 p1, t_vec3 p2)
{
	box->min.x = fmin(p1.x, p2.x);
	box->min.y = fmin(p1.y, p2.y);
	box->min.z = fmin(p1.z, p2.z);
	box->max.x = fmax(p1.x, p2.x);
	box->max.y = fmax(p1.y, p2.y);
	box->max.z = fmax(p1.z, p2.z);
}
