/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:19:38 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:19:39 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/utils/color.h"

int			get_r(int rgb);
int			get_g(int rgb);
int			get_b(int rgb);
int			add_shade(int rgb, double shade_factor);
int			get_opposite(int rgb);

int	get_r(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int	get_g(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int	get_b(int rgb)
{
	return (rgb & 0xFF);
}

int	add_shade(int rgb, double shade_factor)
{
	int	r;
	int	g;
	int	b;

	r = ft_max((int)(get_r(rgb) * shade_factor), 0);
	g = ft_max((int)(get_g(rgb) * shade_factor), 0);
	b = ft_max((int)(get_b(rgb) * shade_factor), 0);
	r = ft_min(r, 255);
	g = ft_min(g, 255);
	b = ft_min(b, 255);
	return (r << 16 | g << 8 | b);
}

int	get_opposite(int rgb)
{
	int	r;
	int	g;
	int	b;

	r = 255 - get_r(rgb);
	g = 255 - get_g(rgb);
	b = 255 - get_b(rgb);
	return (r << 16 | g << 8 | b);
}
