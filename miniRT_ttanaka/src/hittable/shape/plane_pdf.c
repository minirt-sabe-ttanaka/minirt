#include "scene/hittable/shape.h"

double  plane_pdf_value(const void *obj, const t_point3 o, const t_vec3 v);
t_vec3  plane_random(const void *obj, const t_point3 o, unsigned int *seed);

double  plane_pdf_value(const void *obj, const t_point3 o, const t_vec3 v)
{
    (void)obj; (void)o; (void)v;
    return (0.0);
}

t_vec3  plane_random(const void *obj, const t_point3 o, unsigned int *seed)
{
    (void)obj; (void)o; (void)seed;
    return (vec_init(1, 0, 0));
}
