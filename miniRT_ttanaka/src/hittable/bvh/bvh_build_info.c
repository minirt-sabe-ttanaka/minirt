#include "hittable/bvh.h"

t_aabb				calc_centroid_bbox_in_given_range(t_bvh_build_info *info_lst,
						int left, int right);
t_bvh_build_info	*setup_bvh_build_info(t_hittable_lst *objects);
void				swap_build_info(t_bvh_build_info *info_1,
						t_bvh_build_info *info_2);
void				swap_t_hittable(t_hittable *h1, t_hittable *h2);

t_aabb	calc_centroid_bbox_in_given_range(t_bvh_build_info *info_lst, int left,
		int right)
{
	t_aabb	res;
	int		i;
	int		axis;

	init_aabb(&res);
	i = left;
	while (i < right)
	{
		axis = 0;
		while (axis < 3)
		{
			res.min.v[axis] = fmin(res.min.v[axis],
					info_lst[i].centroid.v[axis]);
			res.max.v[axis] = fmax(res.max.v[axis],
					info_lst[i].centroid.v[axis]);
			axis++;
		}
		i++;
	}
	return (res);
}

t_bvh_build_info	*setup_bvh_build_info(t_hittable_lst *objects)
{
	int					i;
	t_bvh_build_info	*info_lst;

	info_lst = (t_bvh_build_info *)malloc(sizeof(t_bvh_build_info)
			* objects->size);
	if (!info_lst)
		return (NULL);
	i = 0;
	while (i < objects->size)
	{
		objects->objects[i].vtable->bbox(objects->objects[i].object,
			&info_lst[i].bbox);
		info_lst[i].centroid = calc_centroid_of_bbox(&info_lst[i].bbox);
		info_lst[i].original_index = i;
		info_lst[i].hittable_p = &(objects->objects[i]);
		i++;
	}
	return (info_lst);
}

void	swap_build_info(t_bvh_build_info *info_1, t_bvh_build_info *info_2)
{
	t_bvh_build_info	tmp;
	t_hittable			*ptr1;
	t_hittable			*ptr2;

	ptr1 = info_1->hittable_p;
	ptr2 = info_2->hittable_p;	
	tmp = *info_1;
	*info_1 = *info_2;
	*info_2 = tmp;
	info_1->hittable_p = ptr1;
	info_2->hittable_p = ptr2;
}

void	swap_t_hittable(t_hittable *h1, t_hittable *h2)
{
	t_hittable	tmp;

	tmp = *h1;
	*h1 = *h2;
	*h2 = tmp;
}
