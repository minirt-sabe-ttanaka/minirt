#include "minirt.h"

void hittable_lst_init(t_hittable_lst *lst);
void hittable_lst_free(t_hittable_lst *lst);
void hittable_lst_add(t_hittable_lst *lst, t_hittable object);
bool hittable_lst_hit(const void *object, const t_ray *r, double t_min, double t_max, t_hit_record *rec);
t_hittable create_hittable_lst(t_hittable_lst *lst);

void hittable_lst_init(t_hittable_lst *lst)
{
    lst->objects = NULL;
    lst->size = 0;
    lst->capacity = 0;
}

void hittable_lst_free(t_hittable_lst *lst)
{
    free(lst->objects);
    hittable_lst_init(lst);
}

void hittable_lst_add(t_hittable_lst *lst, t_hittable object)
{
    int new_capacity;
    t_hittable *new_objs;

    if (lst->size == lst->capacity)
    {
        if (lst->capacity < 8)
            new_capacity = 8;
        else
            new_capacity = lst->capacity * 2;
        new_objs = (t_hittable *)malloc(sizeof(t_hittable) * new_capacity);
        for (int i = 0; i < lst->size; i++)
        {
            new_objs[i] = lst->objects[i];
        }
        free(lst->objects);
        lst->objects = new_objs;
        lst->capacity = new_capacity;
    }
    lst->objects[lst->size++] = object;
}

bool hittable_lst_hit(const void *object, const t_ray *r, double t_min, double t_max, t_hit_record *rec)
{
    const t_hittable_lst *lst = (const t_hittable_lst *)object;
    t_hit_record tmp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (int i = 0; i < lst->size; i++)
    {
        t_hittable cur_object = lst->objects[i];
        if (cur_object.vtable->hit(cur_object.object, r, t_min, closest_so_far, &tmp_rec))
        {
            hit_anything = true;
            closest_so_far = tmp_rec.t;
            *rec = tmp_rec;
        }
    }
    return (hit_anything);
}

t_hittable create_hittable_lst(t_hittable_lst *lst)
{
    static const t_hittable_vtable lst_vtable = { hittable_lst_hit };

    t_hittable h;
    h.object = lst;
    h.vtable = &lst_vtable;
    return (h);
}
