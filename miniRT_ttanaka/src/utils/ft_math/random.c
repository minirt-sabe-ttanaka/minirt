/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:19:30 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 15:22:46 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/utils/ft_math.h"

unsigned int	init_seed(void);
int				my_rand(unsigned int *seed);
double			random_double(unsigned int *seed);
double			random_double_range(unsigned int *seed, double min, double max);
int				random_int_range(unsigned int *seed, int min, int max);

unsigned int	init_seed(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned int)tv.tv_usec);
}

int	my_rand(unsigned int *seed)
{
	*seed = *seed * 1103515245 + 12345;
	return ((*seed / 65536) % 32768);
}

double	random_double(unsigned int *seed)
{
	return (my_rand(seed) / 32768.0);
}

double	random_double_range(unsigned int *seed, double min, double max)
{
	return (min + (max - min) * random_double(seed));
}

int	random_int_range(unsigned int *seed, int min, int max)
{
	return ((int)(min + (max - min + 1) * random_double(seed)));
}
