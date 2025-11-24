/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:20:50 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:20:51 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/utils/vector.h"

t_vec3		vec_init(double x, double y, double z);
t_point3	point_init(double x, double y, double z);

t_vec3	vec_init(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_point3	point_init(double x, double y, double z)
{
	return (vec_init(x, y, z));
}
