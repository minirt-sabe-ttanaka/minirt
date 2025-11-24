/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:20:45 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:20:46 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/utils/vector.h"

t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_mult(t_vec3 a, t_vec3 b);
t_vec3		vec_scale(t_vec3 v, double s);


t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return (vec_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return (vec_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec_mult(t_vec3 a, t_vec3 b)
{
	return (vec_init(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3	vec_scale(t_vec3 v, double s)
{
	return (vec_init(v.x * s, v.y * s, v.z * s));
}
