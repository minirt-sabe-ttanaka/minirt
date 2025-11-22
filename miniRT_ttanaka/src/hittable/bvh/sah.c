#include "hittable/bvh.h"

static void		accumulate_surface_area(t_bucket *buckets, double *left_res,
					double *right_res);
static double	calc_min_cost_in_given_axis(t_bucket *buckets,
					t_bucket_predicate *pred, int n_hittables);
static int		min_idx_of_db_arr(double *arr, int size);
int				split_based_on_sah(t_bvh_build_node *node,
					t_bvh_build_info *info_lst, int left, int right);

static void	accumulate_surface_area(t_bucket *buckets, double *left_res,
		double *right_res)
{
	int		i;
	t_aabb	left_bbox_cur;
	t_aabb	right_bbox_cur;

	init_aabb(&left_bbox_cur);
	init_aabb(&right_bbox_cur);
	i = 0;
	while (i < N_BUCKETS)
	{
		left_bbox_cur = merge_bbox(&buckets[i].bbox, &left_bbox_cur);
		left_res[i] = calc_surface_area_of_bbox(&left_bbox_cur);
		right_bbox_cur = merge_bbox(&buckets[N_BUCKETS - 1 - i].bbox,
				&right_bbox_cur);
		right_res[N_BUCKETS - 1
			- i] = calc_surface_area_of_bbox(&right_bbox_cur);
		i++;
	}
}

static double	calc_min_cost_in_given_axis(t_bucket *buckets,
		t_bucket_predicate *pred, int n_hittables)
{
	int		i;
	int		left_cnt;
	double	min_tmp_cost[2];
	double	accumulate_surface_area_of_left_bbox[N_BUCKETS];
	double	accumulate_surface_area_of_right_bbox[N_BUCKETS];

	min_tmp_cost[0] = COST_ISECT * n_hittables;
	accumulate_surface_area(buckets, accumulate_surface_area_of_left_bbox,
		accumulate_surface_area_of_right_bbox);
	if (accumulate_surface_area_of_left_bbox[N_BUCKETS - 1] == 0.0)
		return (min_tmp_cost[0]);
	i = 1;
	left_cnt = 0;
	pred->split_bucket_id = -1;
	while (i < N_BUCKETS)
	{
		left_cnt += buckets[i - 1].count;
		if (left_cnt == 0 || left_cnt == n_hittables)
		{
			i++;
			continue ;
		}
		min_tmp_cost[1] = COST_TRAV + ((left_cnt * COST_ISECT)
				* (accumulate_surface_area_of_left_bbox[i - 1]
					/ accumulate_surface_area_of_left_bbox[N_BUCKETS - 1])
				+ ((n_hittables - left_cnt) * COST_ISECT)
				* (accumulate_surface_area_of_right_bbox[i]
					/ accumulate_surface_area_of_left_bbox[N_BUCKETS - 1]));
		if (min_tmp_cost[0] > min_tmp_cost[1])
		{
			min_tmp_cost[0] = min_tmp_cost[1];
			pred->split_bucket_id = i;
		}
		i++;
	}
	return (min_tmp_cost[0]);
}

static int	min_idx_of_db_arr(double *arr, int size)
{
	int	i;
	int	res;
	int	cur_min;

	res = 0;
	cur_min = arr[0];
	i = 0;
	while (i < size)
	{
		if (arr[i] < cur_min)
		{
			res = i;
			cur_min = arr[i];
		}
		i++;
	}
	return (res);
}

int	split_based_on_sah(t_bvh_build_node *node, t_bvh_build_info *info_lst,
		int left, int right)
{
	t_bucket_predicate	pred;
	t_bucket			buckets[N_BUCKETS];
	double				costs[3];
	int					split_bucket_ids[3];
	int					axis;

	pred.n_buckets = N_BUCKETS;
	pred.centroid_bbox = calc_centroid_bbox_in_given_range(info_lst, left,
			right);
	axis = -1;
	while (++axis < 3)
	{
		pred.axis = axis;
		init_bucket_lst(buckets, N_BUCKETS);
		assign_info_to_buckets(buckets, info_lst, &pred, &((t_range){left,
				right}));
		costs[axis] = calc_min_cost_in_given_axis(buckets, &pred, (right
					- left));
		split_bucket_ids[axis] = pred.split_bucket_id;
	}
	node->split_axis = min_idx_of_db_arr(costs, 3);
	pred.split_bucket_id = split_bucket_ids[node->split_axis];
	if (pred.split_bucket_id == -1)
		return (left);
	return (partition_infos(info_lst, left, right, &pred));
}
