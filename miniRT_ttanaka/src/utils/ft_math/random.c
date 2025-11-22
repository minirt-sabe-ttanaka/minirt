#include "utils/ft_math.h"

unsigned int	init_seed(void);
int				my_rand(void);
double			random_double(void);
double			random_double_range(double min, double max);

unsigned int	init_seed(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned int)tv.tv_usec);
}

int	my_rand(void)
{
	static unsigned int	seed;
	static bool			is_initialized = false;

	if (is_initialized == false)
	{
		seed = init_seed();
		is_initialized = true;
	}
	seed = seed * 1103515245 + 12345;
	return ((seed / 65536) % 32768);
}

double	random_double(void)
{
	return (my_rand() / 32768.0);
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}
