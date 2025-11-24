/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:51 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:23:02 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/material.h"

void	destroy_default_material(void **object_ptr)
{
	if (object_ptr && *object_ptr)
	{
		free(*object_ptr);
		*object_ptr = NULL;
	}
}
