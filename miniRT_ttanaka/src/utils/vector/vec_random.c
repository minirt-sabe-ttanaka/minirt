/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_random.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:20:43 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 23:55:18 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/utils/vector.h"

t_vec3			random_in_unit_sphere(unsigned int *seed);
t_vec3			random_unit_vector(unsigned int *seed);
t_vec3			random_cosine_direction(unsigned int *seed);

t_vec3	random_in_unit_sphere(unsigned int *seed)
{
	double	a;
	double	z;
	double	r;

	a = random_double_range(seed, 0, 2 * M_PI);
	z = random_double_range(seed, -1, 1);
	r = sqrt(1 - z * z);
	return (vec_init(r * cos(a), r * sin(a), z));
}

t_vec3	random_unit_vector(unsigned int *seed)
{
	return (vec_normalize(random_in_unit_sphere(seed)));
}

t_vec3	random_cosine_direction(unsigned int *seed)
{
	double r1;
	double r2;
	t_vec3 res;

	r1 = random_double_range(seed, 0, 2 * M_PI);
	r2 = random_double(seed);
	res.x = cos(r1) * sqrt(1 - r2);
	res.y = sin(r1) * sqrt(1 - r2);
	res.z = sqrt(r2);
	return (res);
}