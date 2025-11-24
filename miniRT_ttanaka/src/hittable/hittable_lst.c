#include "hittable/hittable_lst.h"

void		hittable_lst_init(t_hittable_lst *lst);
int			hittable_lst_add(t_hittable_lst *lst, t_hittable object);
bool		hittable_lst_hit(const void *object, const t_ray *r, t_double_range range, t_hit_record *rec);
t_hittable	create_hittable_lst(t_hittable_lst *lst);
bool		hittable_lst_bbox(const void *object, t_aabb *output_bbox);

void	hittable_lst_init(t_hittable_lst *lst)
{
	lst->objects = NULL;
	lst->size = 0;
	lst->capacity = 0;
}

int	hittable_lst_add(t_hittable_lst *lst, t_hittable object)
{
	int			i;
	int			new_capacity;
	t_hittable	*new_objs;

	if (lst->size == lst->capacity)
	{
		if (lst->capacity < 8)
			new_capacity = 8;
		else
			new_capacity = lst->capacity * 2;
		new_objs = (t_hittable *)malloc(sizeof(t_hittable) * new_capacity);
		i = -1;
		while (++i < lst->size)
			new_objs[i] = lst->objects[i];
		free(lst->objects);
		lst->objects = new_objs;
		lst->capacity = new_capacity;
	}
	lst->objects[lst->size++] = object;
	return (true);
}

bool	hittable_lst_hit(const void *object, const t_ray *r, t_double_range range, t_hit_record *rec)
{
	(void)object;
	(void)r;
	(void)range;
	(void)rec;
	return (true);
	// const t_hittable_lst	*lst = (const t_hittable_lst *)object;
	// t_hit_record			tmp_rec;
	// bool					hit_anything;
	// double					closest_so_far;
	// t_hittable				cur_object;
	// hit_anything = false;
	// closest_so_far = t_max;
	// for (int i = 0; i < lst->size; i++)
	// {
	// 	cur_object = lst->objects[i];
	// 	if (cur_object.vtable->hit(cur_object.object, r, t_min, closest_so_far,
	// 			&tmp_rec))
	// 	{
	// 		hit_anything = true;
	// 		closest_so_far = tmp_rec.t;
	// 		*rec = tmp_rec;
	// 	}
	// }
	// return (hit_anything);
}

t_hittable	create_hittable_lst(t_hittable_lst *lst)
{
	static const t_hittable_vtable	lst_vtable = {hittable_lst_hit,
			hittable_lst_bbox, NULL };
	t_hittable						h;

	h.object = lst;
	h.vtable = &lst_vtable;
	return (h);
}

bool	hittable_lst_bbox(const void *object, t_aabb *output_bbox)
{
	const t_hittable_lst	*lst = (t_hittable_lst *)object;
	t_aabb					temp_box;
	bool					first_box;
	int						i;

	if (lst->size == 0)
		return (false);
	first_box = true;
	i = 0;
	while (i < lst->size)
	{
		if (!lst->objects[i].vtable->bbox(&lst->objects[i].object, &temp_box))
			return (false);
		if (first_box)
			*output_bbox = temp_box;
		else
			*output_bbox = merge_bbox(output_bbox, &temp_box);
		first_box = false;
		i++;
	}
	return (true);
}
