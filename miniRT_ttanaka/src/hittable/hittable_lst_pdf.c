#include "scene/hittable/hittable_lst.h"

double  hittable_lst_pdf_value(const void *obj, const t_point3 o, const t_vec3 v);
t_vec3  hittable_lst_random(const void *obj, const t_point3 o, unsigned int *seed);

double  hittable_lst_pdf_value(const void *obj, const t_point3 o, const t_vec3 v)
{
    const t_hittable_lst *lst;
    double  sum;
    int     i;

    lst = (const t_hittable_lst *)obj;
    if (lst->size == 0)
        return (0.0);
    sum = 0.0;
    i = 0;
    while (i < lst->size)
    {
        sum += lst->objects[i].vtable->pdf_value(
                    lst->objects[i].object, o, v);
        i++;
    }
    return (sum / lst->size);
}

t_vec3  hittable_lst_random(const void *obj, const t_point3 o, unsigned int *seed)
{
    const t_hittable_lst *lst;
    int     random_index;

    lst = (const t_hittable_lst *)obj;
    if (lst->size == 0)
        return (vec_init(1, 0, 0));
    random_index = random_int_range(seed, 0, lst->size - 1);
    return (lst->objects[random_index].vtable->random(
                lst->objects[random_index].object, o, seed));
}
