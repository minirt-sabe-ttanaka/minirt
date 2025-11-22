#include "hittable/bvh.h"

t_bvh_traversal	init_traversal_info(const void *object, const t_ray *r,
					double t_min, double t_max, t_hit_record *rec);
void			hit_leaf_objects(t_bvh_traversal *info,
					const t_linear_bvh_node *node);
void			push_child_nodes_to_stack(t_bvh_traversal *info,
					const t_linear_bvh_node *node, int cur_node_idx);

t_bvh_traversal	init_traversal_info(const void *object, const t_ray *r,
		double t_min, double t_max, t_hit_record *rec)
{
	t_bvh_traversal	info;
	int				axis;

	info.bvh = (const t_linear_bvh *)object;
	info.closest_so_far = t_max;
	axis = -1;
	while (++axis < 3)
		info.dir_is_neg[axis] = r->dir.v[axis];
	info.hit = false;
	info.r = r;
	info.rec = rec;
	info.t_min = t_min;
	info.to_visit_idx = 0;
	return (info);
}

void	hit_leaf_objects(t_bvh_traversal *info, const t_linear_bvh_node *node)
{
	int				i;
	int 			end_idx;
	t_hittable		*hittable;
	t_hit_record	tmp_rec;

	i = node->hittale_idx;
	end_idx = node->hittale_idx + node->n_hittables;
	while (i < end_idx)
	{
		hittable = &(info->bvh->objects->objects[i]);
		if (hittable->vtable->hit(hittable, info->r, info->t_min,
				info->closest_so_far, &tmp_rec))
		{
			info->closest_so_far = tmp_rec.t;
			*(info->rec) = tmp_rec;
			info->hit = true;
		}
		i++;
	}
}

void	push_child_nodes_to_stack(t_bvh_traversal *info,
		const t_linear_bvh_node *node, int cur_node_idx)
{
	if (info->dir_is_neg[node->axis])
	{
		info->nodes_to_visit[info->to_visit_idx++] = cur_node_idx + 1;
		info->nodes_to_visit[info->to_visit_idx++] = node->right_child_idx;
	}
	else
	{
		info->nodes_to_visit[info->to_visit_idx++] = node->right_child_idx;
		info->nodes_to_visit[info->to_visit_idx++] = cur_node_idx + 1;
	}
}
