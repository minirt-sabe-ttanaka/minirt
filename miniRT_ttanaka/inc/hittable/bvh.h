#ifndef BVH_H
# define BVH_H

# include "hittable/base_hittable.h"
# include "hittable/hittable_lst.h"

typedef struct s_bvh_build_node
{
	t_aabb						bbox;
	struct s_bvh_build_node			*left;
	struct s_bvh_build_node			*right;
	int							first_hittable_idx;
	int							n_hittables;
	int							split_axis;
}								t_bvh_build_node;

typedef struct s_bvh_build
{
	t_bvh_build_node			*root;
	int							n_nodes;
}								t_bvh_build;

typedef struct s_bvh_build_info
{
	t_vec3						centroid;
	t_aabb						bbox;
	int							original_index;
	t_hittable					*hittable_p;
}								t_bvh_build_info;

typedef struct s_linear_bvh_node
{
	t_aabb						bbox;
	union
	{
		int						hittale_idx;
		int						right_child_idx;
	};
	uint16_t					n_hittables;
	uint8_t						axis;
}								t_linear_bvh_node;

typedef struct s_linear_bvh
{
	t_linear_bvh_node			*bvh_nodes;
	t_hittable_lst				*objects;
	int							length;
}								t_linear_bvh;

t_linear_bvh					*bvh_init(t_hittable_lst *objects);
bool							bvh_hit(const void *object, const t_ray *r,
									double t_min, double t_max,
									t_hit_record *rec);
t_hittable						create_hittable_bvh(t_linear_bvh *bvh);
bool							convert_lst_2_bvh(t_hittable_lst *lst,
									t_hittable **bvh);

typedef struct s_range
{
	int							start;
	int							end;
}								t_range;

typedef struct s_bucket
{
	t_aabb						bbox;
	int							count;
}								t_bucket;

typedef struct s_bucket_predicate
{
	int							axis;
	int							split_bucket_id;
	int							n_buckets;
	t_aabb						centroid_bbox;

}								t_bucket_predicate;

void							init_bucket_lst(t_bucket *bucket, int size);
int								get_bucket_id(const t_bvh_build_info *info,
									const t_bucket_predicate *pred);
void							assign_info_to_buckets(t_bucket *bucket_lst,
									const t_bvh_build_info *info_lst,
									const t_bucket_predicate *pred,
									t_range *range);
t_aabb							merge_bbox_in_given_range(t_bvh_build_info *info_lst,
									int start, int end);

t_aabb							calc_centroid_bbox_in_given_range(t_bvh_build_info *info_lst,
									int left, int right);
t_bvh_build_info				*setup_bvh_build_info(t_hittable_lst *objects);
void							swap_build_info(t_bvh_build_info *info_1,
									t_bvh_build_info *info_2);
void							swap_t_hittable(t_hittable *h1, t_hittable *h2);

int								get_bucket_id(const t_bvh_build_info *info,
									const t_bucket_predicate *pred);

int								partition_infos(t_bvh_build_info *info,
									int start, int end,
									const t_bucket_predicate *pred);

int								split_based_on_sah(t_bvh_build_node *node,
									t_bvh_build_info *info_lst, int left,
									int right);

t_bvh_build						*build_bvh_recursive(t_hittable_lst *objects);
t_linear_bvh					*flatten_bvh(t_bvh_build *bvh_build,
									t_hittable_lst *objects);

typedef struct s_bvh_traversal
{
	const t_linear_bvh			*bvh;
	const t_ray					*r;
	t_vec3						inv_dir;
	int							dir_is_neg[3];
	double						t_min;

	t_hit_record				*rec;
	bool						hit;
	double						closest_so_far;

	int							nodes_to_visit[64];
	int							to_visit_idx;

}								t_bvh_traversal;

t_bvh_traversal					init_traversal_info(const void *object,
									const t_ray *r, double t_min, double t_max,
									t_hit_record *rec);
void							hit_leaf_objects(t_bvh_traversal *info,
									const t_linear_bvh_node *node);
void							push_child_nodes_to_stack(t_bvh_traversal *info,
									const t_linear_bvh_node *node,
									int cur_node_idx);

#endif