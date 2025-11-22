#include "utils/vector.h"

t_vec3			random_in_unit_sphere(void);
t_vec3			random_unit_vector(void);

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
