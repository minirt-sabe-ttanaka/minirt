/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:19:34 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:19:35 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/utils/ft_math.h"

int		ft_max(int x, int y);
int		ft_min(int x, int y);
int		ft_abs(int x);
void	ft_swap(int *x, int *y);
bool	ft_solve_quadratic_equation(double a, double b, double c, double *res);

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

int	ft_min(int x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

int	ft_abs(int x)
{
	if (x < 0)
		x *= -1;
	return (x);
}

void	ft_swap(int *x, int *y)
{
	int	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

bool	ft_solve_quadratic_equation(double a, double b, double c, double *res)
{
	double d;

	d = b * b - 4 * a * c;
	if (d < 0)
		return (false);
    if (a == 0)
    {
        res[0] = -c / b;
        res[1] = -c / b;
        return (true);
    }
	res[0] = (-b - sqrt(d)) / (2 * a);
	res[1] = (-b + sqrt(d)) / (2 * a);
	return (true);
}