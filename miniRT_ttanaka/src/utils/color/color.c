/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:19:36 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:19:37 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/utils/color.h"

t_color3	color_init(double r, double g, double b);
t_color3	rgb2color(u_int8_t r, u_int8_t g, u_int8_t b);

t_color3	color_init(double r, double g, double b)
{
	t_color3	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color3	rgb2color(u_int8_t r, u_int8_t g, u_int8_t b)
{
	return (color_init(r / 255.0, g / 255.0, b / 255.0));
}
