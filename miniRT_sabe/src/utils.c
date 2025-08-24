/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesouichirou <abesouichirou@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:17:14 by abesouichir       #+#    #+#             */
/*   Updated: 2025/08/22 14:55:11 by abesouichir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

t_vec3 refract(t_vec3 v, t_vec3 n, double eta_ratio) {
    double cos_theta = vec3_dot(vec3_neg(v), n);
    t_vec3 r_out_perp = vec3_mul_s(vec3_add(v, vec3_mul_s(n, cos_theta)), eta_ratio);
    t_vec3 r_out_parallel = vec3_mul_s(n, -sqrt(fabs(1.0 - vec3_length2(r_out_perp))));
    return vec3_add(r_out_perp, r_out_parallel);
}

double schlick(double cos_theta, double eta_ratio) {
    double r0 = (1.0 - eta_ratio) / (1.0 + eta_ratio);
    r0 *= r0;
    return r0 + (1.0 - r0) * pow(1.0 - cos_theta, 5);
}