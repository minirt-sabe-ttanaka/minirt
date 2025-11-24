#include "utils/vector.h"

t_vec3			random_in_unit_sphere(unsigned int *seed);
t_vec3			random_unit_vector(unsigned int *seed);

t_vec3	random_in_unit_sphere(unsigned int *seed)
{
	double	a;
	double	z;
	double	r;

	a = random_double_range(seed, 0, 2 * M_PI);
	z = random_double_range(seed, -1, 1);
	r = sqrt(1 - z * z);
	return (vec_init(r * cos(a), r * sin(a), z));
}

t_vec3	random_unit_vector(unsigned int *seed)
{
	return (vec_normalize(random_in_unit_sphere(seed)));
}
