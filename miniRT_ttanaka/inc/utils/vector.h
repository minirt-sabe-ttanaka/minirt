/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:23:52 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/21 22:08:00 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "ft_math.h"
# include <math.h>
# include <stdbool.h>

typedef struct s_vec3
{
	union
	{
		struct
		{
			double x, y, z;
		};
		struct
		{
			double r, g, b;
		};
		double v[3];
	};
}				t_vec3;

typedef t_vec3	t_point3;

t_vec3			vec_init(double x, double y, double z);
t_point3		point_init(double x, double y, double z);

t_vec3			vec_add(t_vec3 a, t_vec3 b);
t_vec3			vec_sub(t_vec3 a, t_vec3 b);
t_vec3			vec_mult(t_vec3 a, t_vec3 b);
t_vec3			vec_scale(t_vec3 v, double s);
double			vec_dot(t_vec3 a, t_vec3 b);
t_vec3			vec_cross(t_vec3 a, t_vec3 b);
double			vec_norm_squared(t_vec3 v);
double			vec_norm(t_vec3 v);
t_vec3			vec_normalize(t_vec3 v);
bool			vec_near_zero(t_vec3 v);
t_vec3			vec_reflect(t_vec3 v, t_vec3 n);
t_vec3			vec_refract(t_vec3 uv, t_vec3 n, double etai_over_etat);
double			schlick(double cosine, double ref_idx);

t_vec3			random_in_unit_sphere(void);
t_vec3			random_unit_vector(void);

#endif