#include "hittable/bvh.h"

static void	_init_bucket(t_bucket *bucket);
void		init_bucket_lst(t_bucket *bucket, int size);
int			get_bucket_id(const t_bvh_build_info *info,
				const t_bucket_predicate *pred);
void		assign_info_to_buckets(t_bucket *bucket_lst,
				const t_bvh_build_info *info_lst,
				const t_bucket_predicate *pred, t_range *range);
t_aabb		merge_bbox_in_given_range(t_bvh_build_info *info_lst, int start,
				int end);

static void	_init_bucket(t_bucket *bucket)
{
	bucket->bbox.min = vec_init(INFINITY, INFINITY, INFINITY);
	bucket->bbox.max = vec_init(-INFINITY, -INFINITY, -INFINITY);
	bucket->count = 0;
}

void	init_bucket_lst(t_bucket *bucket, int size)
{
	int	i;

	i = 0;
	while (i < size)
		_init_bucket(&bucket[i++]);
}

int	get_bucket_id(const t_bvh_build_info *info, const t_bucket_predicate *pred)
{
	double	centroid_coord;
	double	min;
	double	max;
	double	id;

	centroid_coord = info->centroid.v[pred->axis];
	min = pred->centroid_bbox.min.v[pred->axis];
	max = pred->centroid_bbox.max.v[pred->axis];
	if (max - min == 0)
		return (0);
	id = (int)((centroid_coord - min) * pred->n_buckets / (max - min));
	if (id < 0)
		return (0);
	if (id >= pred->n_buckets)
		return (pred->n_buckets - 1);
	return (id);
}

void	assign_info_to_buckets(t_bucket *bucket_lst,
		const t_bvh_build_info *info_lst, const t_bucket_predicate *pred,
		t_range *range)
{
	int	i;
	int	id;

	i = range->start;
	while (i < range->end)
	{
		id = get_bucket_id(&(info_lst[i]), pred);
		bucket_lst[id].count++;
		bucket_lst[id].bbox = merge_bbox(&(bucket_lst[id].bbox),
				&(info_lst[i].bbox));
		i++;
	}
}

t_aabb	merge_bbox_in_given_range(t_bvh_build_info *info_lst, int start,
		int end)
{
	t_aabb	res;
	int		i;
	int		axis;

	init_aabb(&res);
	i = start;
	while (i < end)
	{
		axis = 0;
		while (axis < 3)
		{
			res.min.v[axis] = fmin(res.min.v[axis],
					info_lst[i].bbox.min.v[axis]);
			res.max.v[axis] = fmax(res.max.v[axis],
					info_lst[i].bbox.max.v[axis]);
			axis++;
		}
		i++;
	}
	return (res);
}
