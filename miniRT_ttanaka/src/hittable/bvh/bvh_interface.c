/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_interface.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:17:08 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:17:09 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/hittable/bvh.h"

void			destroy_bvh_build(t_bvh_build *bvh_build);
t_linear_bvh	*bvh_init(t_hittable_lst *objects);
bool			bvh_hit(const void *object, const t_ray *r,
					t_double_range range, t_hit_record *rec);
t_hittable		create_hittable_bvh(t_linear_bvh *bvh);
bool			convert_lst_2_bvh(t_hittable_lst *lst, t_hittable **bvh);
bool			bvh_bbox(const void *object, t_aabb *output_bbox);

t_linear_bvh	*bvh_init(t_hittable_lst *objects)
{
	t_bvh_build		*bvh_build;
	t_linear_bvh	*linear_bvh;

	bvh_build = build_bvh_recursive(objects);
	if (!bvh_build)
		return (NULL);
	linear_bvh = flatten_bvh(bvh_build, objects);
	destroy_bvh_build(bvh_build);
	return (linear_bvh);
}

bool	bvh_hit(const void *object, const t_ray *r, t_double_range range,
		t_hit_record *rec)
{
	t_bvh_traversal			info;
	int						cur_node_idx;
	const t_linear_bvh_node	*node;

	info = init_traversal_info(object, r, range, rec);
	cur_node_idx = 0;
	while (true)
	{
		node = &info.bvh->bvh_nodes[cur_node_idx];
		if (aabb_hit(&node->bbox, r, (t_double_range){range.min,
				info.closest_so_far}))
		{
			if (node->n_hittables > 0)
				hit_leaf_objects(&info, node);
			else
				push_child_nodes_to_stack(&info, node, cur_node_idx);
		}
		if (info.to_visit_idx == 0)
			break ;
		cur_node_idx = info.nodes_to_visit[--info.to_visit_idx];
	}
	return (info.hit);
}

t_hittable	create_hittable_bvh(t_linear_bvh *bvh)
{
	t_hittable						h;
	static const t_hittable_vtable	lst_vtable = {bvh_hit, bvh_bbox, NULL};

	h.object = bvh;
	h.vtable = &lst_vtable;
	return (h);
}

bool	convert_lst_2_bvh(t_hittable_lst *lst, t_hittable **bvh)
{
	t_linear_bvh	*linear_bvh;

	linear_bvh = bvh_init(lst);
	if (!linear_bvh)
		return (false);
	*bvh = (t_hittable *)malloc(sizeof(t_hittable));
	if (!(*bvh))
		return (false);
	**bvh = create_hittable_bvh(linear_bvh);
	return (true);
}

bool	bvh_bbox(const void *object, t_aabb *output_bbox)
{
	const t_linear_bvh	*bvh_linear;

	bvh_linear = (const t_linear_bvh *)object;
	if (!bvh_linear->bvh_nodes || bvh_linear->length == 0)
		return (false);
	*output_bbox = bvh_linear->bvh_nodes[0].bbox;
	return (true);
}
