/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesouichirou <abesouichirou@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:46:25 by abesouichir       #+#    #+#             */
/*   Updated: 2025/08/22 11:58:13 by abesouichir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_camera camera_create(t_point3 origin, t_vec3 horizontal, t_vec3 vertical, t_vec3 lower_left_corner) {
    t_camera cam;
    cam.origin = origin;
    cam.horizontal = horizontal;
    cam.vertical = vertical;
    cam.lower_left_corner = lower_left_corner;
    return cam;
}

t_ray camera_get_ray(const t_camera *cam, double u, double v) {
    t_vec3 direction = vec3_sub(
        vec3_add(
            vec3_add(cam->lower_left_corner, vec3_mul_s(cam->horizontal, u)),
            vec3_mul_s(cam->vertical, v)
        ),
        cam->origin
    );
    return (t_ray){cam->origin, direction};
  }