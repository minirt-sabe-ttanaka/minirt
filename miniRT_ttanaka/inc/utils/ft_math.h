/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:23:47 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/23 02:33:15 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include <math.h>
# include <stdbool.h>
# include <sys/time.h>

int				ft_max(int x, int y);
int				ft_min(int x, int y);
int				ft_abs(int x);
void			ft_swap(int *x, int *y);
bool			ft_solve_quadratic_equation(double a, double b, double c,
					double *res);

unsigned int	init_seed(void);
int				my_rand(void);
double			random_double(void);
double			random_double_range(double min, double max);

double			ft_clamp(double x, double min, double max);

#endif