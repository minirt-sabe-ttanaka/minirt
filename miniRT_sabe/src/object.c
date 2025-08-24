/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesouichirou <abesouichirou@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:32:40 by abesouichir       #+#    #+#             */
/*   Updated: 2025/08/19 19:16:17 by abesouichir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void hittable_lst_init(t_hittable_lst *lst) {
    lst->objects = NULL; lst->size = 0; lst->capacity = 0;
}

int ensure_capacity(t_hittable_lst *lst, int min)
{
    if (lst->capacity >= min) return (0);
    int new_capacity = lst->capacity ? lst->capacity * 2 : 4;
    if (new_capacity < min) new_capacity = min;
    t_hittable *new_objects = malloc(new_capacity * sizeof(t_hittable));
    if (!new_objects) {
        perror("Failed to allocate memory for hittable list");
        return (1);
    }
    ft_memcpy(new_objects, lst->objects, lst->size * sizeof(t_hittable));
    free(lst->objects);
    lst->objects = new_objects;
    lst->capacity = new_capacity;
    return (0);
}

int hittable_lst_push(t_hittable_lst *lst, const void *object, const t_hittable_vtable *vtable) {
    if (ensure_capacity(lst, lst->size + 1) != 0) return (-1);
    lst->objects[lst->size].object = object;
    lst->objects[lst->size].vtable  = vtable;
    lst->size++;
    return (0);
}

bool hit_hittable_lst(const t_hittable_lst *lst, const t_ray *r, double t_min, double t_max, t_hit_record *rec) {
    t_hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i = 0; i < lst->size; i++) {
        const t_hittable *hittable = &lst->objects[i];
        if (hittable->vtable->hit(hittable->object, r, t_min, closest_so_far, &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }
    return hit_anything;
}