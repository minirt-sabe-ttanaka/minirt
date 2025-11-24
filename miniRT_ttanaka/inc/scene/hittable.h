/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:20 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:23:39 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

# include "scene/hittable/base_hittable.h"
# include "scene/hittable/bvh.h"
# include "scene/hittable/hittable_lst.h"
# include "struct.h"

void	destroy_bvh_build(t_bvh_build *bvh_build);
void	destroy_hittable_lst(t_hittable_lst *lst);
void	destroy_linear_bvh(t_linear_bvh *bvh);

#endif