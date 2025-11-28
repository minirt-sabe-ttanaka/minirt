/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:17 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 17:41:31 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H

# include "core/ray.h"
# include "core/utils.h"
# include "rt_struct.h"
# include <float.h>

typedef struct s_aabb
{
	t_vec3	min;
	t_vec3	max;
}			t_aabb;

bool		aabb_hit(const t_aabb *bbox, const t_ray *r, t_double_range range);
t_aabb		merge_bbox(const t_aabb *bbox_0, const t_aabb *bbox_1);
t_vec3		calc_centroid_of_bbox(const t_aabb *bbox);
double		calc_surface_area_of_bbox(const t_aabb *bbox);
void		init_aabb(t_aabb *aabb);
void		set_axis_aabb(t_aabb *box, t_point3 p1, t_point3 p2);
void		update_aabb(t_aabb *box, t_point3 p);

#endif