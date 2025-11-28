/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:20:48 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 18:08:27 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/utils/vector.h"

bool		vec_near_zero(t_vec3 v);
t_vec3		vec_reflect(t_vec3 v, t_vec3 n);
t_vec3		vec_refract(t_vec3 uv, t_vec3 n, double etai_over_etat);
double		schlick(double cosine, double ref_idx);

bool	vec_near_zero(t_vec3 v)
{
	const double	eps = 1e-8;

	if (fabs(v.x) < eps && fabs(v.y) < eps && fabs(v.z) < eps)
		return (true);
	return (false);
}

t_vec3	vec_reflect(t_vec3 v, t_vec3 n)
{
	double	dot_vn;
	t_vec3	scaled_n;

	dot_vn = vec_dot(v, n);
	scaled_n = vec_scale(n, 2 * dot_vn);
	return (vec_sub(v, scaled_n));
}

t_vec3	vec_refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = fmin(vec_dot(vec_scale(uv, -1), n), 1.0);
	r_out_perp = vec_scale(vec_add(uv, vec_scale(n, cos_theta)),
			etai_over_etat);
	r_out_parallel = vec_scale(n, -sqrt(fabs(1.0 - vec_norm_squared(r_out_perp))));
	return (vec_add(r_out_perp, r_out_parallel));
}

double	schlick(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}
