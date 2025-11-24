/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 02:25:41 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/24 22:19:12 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"
#include <stdio.h>

bool		aabb_hit(const t_aabb *bbox, const t_ray *r, t_double_range range);
t_aabb		merge_bbox(const t_aabb *bbox_0, const t_aabb *bbox_1);
t_vec3		calc_centroid_of_bbox(const t_aabb *bbox);
double		calc_surface_area_of_bbox(const t_aabb *bbox);

static void	ft_db_swap(double *x1, double *x2)
{
	double	tmp;

	tmp = *x1;
	*x1 = *x2;
	*x2 = tmp;
}

bool	aabb_hit(const t_aabb *bbox, const t_ray *r, t_double_range range)
{
	int		axis;
	double	inv_d;
	double	t0;
	double	t1;

	axis = 0;
	while (axis < 3)
	{
		inv_d = 1.0 / r->dir.v[axis];
		t0 = (bbox->min.v[axis] - r->orig.v[axis]) * inv_d;
		t1 = (bbox->max.v[axis] - r->orig.v[axis]) * inv_d;
		if (t0 > t1)
			ft_db_swap(&t0, &t1);
		range.min = fmax(range.min, t0);
		range.max = fmin(range.max, t1);
		if (range.max <= range.min)
			return (false);
		axis++;
	}
	return (true);
}

t_aabb	merge_bbox(const t_aabb *bbox_0, const t_aabb *bbox_1)
{
	t_aabb	merged_bbox;
	int		axis;

	axis = 0;
	while (axis < 3)
	{
		merged_bbox.min.v[axis] = fmin(bbox_0->min.v[axis],
				bbox_1->min.v[axis]);
		merged_bbox.max.v[axis] = fmax(bbox_0->max.v[axis],
				bbox_1->max.v[axis]);
		axis++;
	}
	return (merged_bbox);
}

t_vec3	calc_centroid_of_bbox(const t_aabb *bbox)
{
	t_vec3	centroid;
	int		axis;

	axis = 0;
	while (axis < 3)
	{
		centroid.v[axis] = (bbox->min.v[axis] + bbox->max.v[axis]) / 2;
		axis++;
	}
	return (centroid);
}

double	calc_surface_area_of_bbox(const t_aabb *bbox)
{
	double edge_len[3];
	int axis;

	axis = 0;
	while (axis < 3)
	{
		edge_len[axis] = bbox->max.v[axis] - bbox->min.v[axis];
		axis++;
	}
	return (2 * (edge_len[0] * edge_len[1] + edge_len[1] * edge_len[2]
			+ edge_len[2] * edge_len[0]));
}
