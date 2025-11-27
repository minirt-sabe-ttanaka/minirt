/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_hittable.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:29 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 15:13:57 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HITTABLE_H
# define BASE_HITTABLE_H

# include "core/ray.h"
# include "core/utils.h"
# include "scene/aabb.h"
# include "scene/material.h"
# include "rt_struct.h"

typedef struct s_hittable_vtable
{
	bool					(*hit)(const void *object, const t_ray *r,
							t_double_range range, t_hit_record *rec);
	bool					(*bbox)(const void *object, t_aabb *output_bbox);
	void					(*destroy)(void *object);
	double					(*pdf_value)(const void *obj, const t_point3 o,
							const t_vec3 v);
	t_vec3					(*random)(const void *obj, const t_point3 o,
							unsigned int *seed);
}							t_hittable_vtable;

typedef struct s_hittable
{
	const void				*object;
	const t_hittable_vtable	*vtable;
}							t_hittable;

#endif