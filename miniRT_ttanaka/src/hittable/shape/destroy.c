/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:17:46 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 23:21:51 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/hittable/shape.h"

void	cylinder_destroy(void *object);
void	plane_destroy(void *object);
void	sphere_destroy(void *object);
void	triangle_destroy(void *object);

void	cylinder_destroy(void *object)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)object;
	if (cy->mat.vtable && cy->mat.vtable->destroy)
	{
		cy->mat.vtable->destroy((void **)&(cy->mat.object));
	}
	free(cy);
}

void	plane_destroy(void *object)
{
	t_plane	*pl;

	pl = (t_plane *)object;
	if (pl->mat.vtable && pl->mat.vtable->destroy)
	{
		pl->mat.vtable->destroy((void **)&(pl->mat.object));
	}
	free(pl);
}

void	sphere_destroy(void *object)
{
	t_sphere	*sp;

	sp = (t_sphere *)object;
	if (sp->mat.vtable && sp->mat.vtable->destroy)
	{
		sp->mat.vtable->destroy((void **)&(sp->mat.object));
	}
	free(sp);
}

void	triangle_destroy(void *object)
{
	t_triangle	*tr;

	tr = (t_triangle *)object;
	if (tr->mat.vtable && tr->mat.vtable->destroy)
	{
		tr->mat.vtable->destroy((void **)&(tr->mat.object));
	}
	free(tr);
}
