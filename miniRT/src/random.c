#include "minirt.h"

unsigned int	init_seed(void);
int				my_rand(void);
double			random_double(void);
double			random_double_range(double min, double max);
t_vec3			random_in_unit_sphere(void);
t_vec3			random_unit_vector(void);

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

t_vec3	random_in_unit_sphere(void)
{
	double	a;
	double	z;
	double	r;

	a = random_double_range(0, 2 * M_PI);
	z = random_double_range(-1, 1);
	r = sqrt(1 - z * z);
	return (vec_init(r * cos(a), r * sin(a), z));
}

t_vec3	random_unit_vector(void)
{
	return (vec_normalize(random_in_unit_sphere()));
}
