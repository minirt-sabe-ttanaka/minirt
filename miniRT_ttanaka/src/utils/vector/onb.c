/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 01:55:55 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 17:05:55 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/utils/vector.h"

void	onb_build_from_w(t_onb *onb, t_vec3 n);
t_vec3	onb_local2world(const t_onb *onb, double a, double b, double c);

void	onb_build_from_w(t_onb *onb, t_vec3 n)
{
	t_vec3	a;

	onb->w = vec_normalize(n);
	if (fabs(onb->w.x) > 0.9)
		a = vec_init(0, 1, 0);
	else
		a = vec_init(1, 0, 0);
	onb->v = vec_normalize(vec_cross(onb->w, a));
	onb->u = vec_cross(onb->v, onb->w);
}

t_vec3	onb_local2world(const t_onb *onb, double a, double b, double c)
{
	t_vec3	res;

	res = vec_scale(onb->u, a);
	res = vec_add(res, vec_scale(onb->v, b));
	res = vec_add(res, vec_scale(onb->w, c));
	return (res);
}
