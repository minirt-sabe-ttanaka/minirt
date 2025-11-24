#ifndef HITTABLE_LST_H
# define HITTABLE_LST_H

# include "aabb.h"
# include "hittable/base_hittable.h"
# include "material.h"
# include "ray.h"
# include "utils.h"
# include <stdalign.h>
# include <stdint.h>
# include <stdlib.h>

# define N_BUCKETS 16
# define COST_TRAV 1.0
# define COST_ISECT 1.0
# define MAX_LEAF_PRIMS 1

typedef struct s_hittable_lst
{
	t_hittable	*objects;
	int			size;
	int			capacity;
}				t_hittable_lst;

void			destroy_hittable_lst(t_hittable_lst *lst);
void			hittable_lst_init(t_hittable_lst *lst);
int				hittable_lst_add(t_hittable_lst *lst, t_hittable object);
bool			hittable_lst_hit(const void *object, const t_ray *r,
					t_double_range range, t_hit_record *rec);
t_hittable		create_hittable_lst(t_hittable_lst *lst);

#endif