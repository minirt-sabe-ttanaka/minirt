/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_random.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:20:43 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:20:44 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/utils/vector.h"

t_vec3			random_in_unit_sphere(unsigned int *seed);
t_vec3			random_unit_vector(unsigned int *seed);

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
