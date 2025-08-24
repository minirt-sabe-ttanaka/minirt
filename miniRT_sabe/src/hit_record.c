/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesouichirou <abesouichirou@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 10:10:49 by abesouichir       #+#    #+#             */
/*   Updated: 2025/08/19 10:11:42 by abesouichir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void set_face_normal(t_hit_record *rec, const t_ray *r, const t_vec3 outward_normal)
{
    rec->front_face = vec3_dot(r->dir, outward_normal) < 0;
    if (rec->front_face)
        rec->normal = outward_normal;
    else
        rec->normal = vec3_neg(outward_normal);
}