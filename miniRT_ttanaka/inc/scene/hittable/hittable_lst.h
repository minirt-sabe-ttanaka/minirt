/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_lst.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:32 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 15:24:19 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LST_H
# define HITTABLE_LST_H

# include "base_hittable.h"
# include "core/ray.h"
# include "core/utils.h"
# include "rt_struct.h"
# include "scene/aabb.h"
# include "scene/material.h"
# include <stdalign.h>
# include <stdint.h>
# include <stdlib.h>

# define N_BUCKETS 16
# define COST_TRAV 1.0
# define COST_ISECT 1.0
# define MAX_LEAF_PRIMS 1

typedef struct s_hittable_lst
{
	t_hittable	*objects;
	int			size;
	int			capacity;
}				t_hittable_lst;

void			hittable_lst_init(t_hittable_lst *lst);
int				hittable_lst_add(t_hittable_lst *lst, t_hittable object);
bool			hittable_lst_hit(const void *object, const t_ray *r,
					t_double_range range, t_hit_record *rec);
t_hittable		create_hittable_lst(t_hittable_lst *lst);
double			hittable_lst_pdf_value(const void *obj, const t_point3 o,
					const t_vec3 v);
t_vec3			hittable_lst_random(const void *obj, const t_point3 o,
					unsigned int *seed);
#endif