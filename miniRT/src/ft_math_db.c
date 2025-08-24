/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_db.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:13:53 by ttanaka           #+#    #+#             */
/*   Updated: 2025/08/17 13:14:31 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_db_max(double x, double y);
double	ft_db_min(double x, double y);
double	ft_db_abs(double x);
void	ft_db_swap(double *x, double *y);

double	ft_db_max(double x, double y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

double	ft_db_min(double x, double y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

double	ft_db_abs(double x)
{
	if (x < 0)
		x *= -1;
	return (x);
}

void	ft_db_swap(double *x, double *y)
{
	double	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}
