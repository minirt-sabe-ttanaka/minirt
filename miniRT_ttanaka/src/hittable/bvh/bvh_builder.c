/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:16:58 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:25:54 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/hittable/bvh.h"

static t_bvh_build_node	*_build_bvh_recursive(t_hittable_lst *objects,
							t_bvh_build_info *info_lst, t_range *range,
							int *count);
t_bvh_build				*build_bvh_recursive(t_hittable_lst *objects);
static int				_flatten_bvh(t_linear_bvh *linear_bvh,
							t_bvh_build_node *build_node, int *offset);
t_linear_bvh			*flatten_bvh(t_bvh_build *bvh_build,
							t_hittable_lst *objects);

static t_bvh_build_node	*_build_bvh_recursive(t_hittable_lst *objects,
		t_bvh_build_info *info_lst, t_range *range, int *count)
{
	t_bvh_build_node	*node;
	int					split_idx;
	int					n_hittables;

	(*count)++;
	node = (t_bvh_build_node *)malloc(sizeof(t_bvh_build_node));
	if (!node)
		return (NULL);
	node->bbox = merge_bbox_in_given_range(info_lst, range);
	n_hittables = range->end - range->start;
	if (n_hittables > MAX_LEAF_PRIMS)
		split_idx = split_based_on_sah(node, info_lst, range);
	if (n_hittables <= MAX_LEAF_PRIMS || split_idx == range->start)
	{
		node->first_hittable_idx = range->start;
		node->n_hittables = n_hittables;
		node->left = NULL;
		node->right = NULL;
	}
	else
	{
		node->n_hittables = 0;
		node->left = _build_bvh_recursive(objects, info_lst,
				&(t_range){range->start, split_idx}, count);
		node->right = _build_bvh_recursive(objects, info_lst,
				&(t_range){split_idx, range->end}, count);
	}
	return (node);
}

t_bvh_build	*build_bvh_recursive(t_hittable_lst *objects)
{
	t_bvh_build			*bvh_build;
	t_bvh_build_info	*info_lst;
	t_bvh_build_node	*root;

	bvh_build = (t_bvh_build *)malloc(sizeof(t_bvh_build));
	if (!bvh_build)
		return (NULL);
	info_lst = setup_bvh_build_info(objects);
	if (!info_lst)
	{
		free(bvh_build);
		return (NULL);
	}
	bvh_build->n_nodes = 0;
	root = _build_bvh_recursive(objects, info_lst, &(t_range){0, objects->size},
			&(bvh_build->n_nodes));
	free(info_lst);
	printf("BVH Nodes created: %d\n", bvh_build->n_nodes);
	bvh_build->root = root;
	return (bvh_build);
}

static int	_flatten_bvh(t_linear_bvh *linear_bvh, t_bvh_build_node *build_node,
		int *offset)
{
	t_linear_bvh_node	*linear_node;
	int					my_offset;

	linear_node = &(linear_bvh->bvh_nodes[*offset]);
	linear_node->bbox = build_node->bbox;
	my_offset = (*offset)++;
	if (build_node->n_hittables > 0)
	{
		linear_node->hittale_idx = build_node->first_hittable_idx;
		linear_node->n_hittables = build_node->n_hittables;
	}
	else
	{
		linear_node->axis = build_node->split_axis;
		linear_node->n_hittables = 0;
		_flatten_bvh(linear_bvh, build_node->left, offset);
		linear_node->right_child_idx = _flatten_bvh(linear_bvh,
				build_node->right, offset);
	}
	return (my_offset);
}

t_linear_bvh	*flatten_bvh(t_bvh_build *bvh_build, t_hittable_lst *objects)
{
	t_linear_bvh	*linear_bvh;
	int				offset;

	linear_bvh = (t_linear_bvh *)malloc(sizeof(t_linear_bvh));
	if (!linear_bvh)
		return (NULL);
	linear_bvh->bvh_nodes = (t_linear_bvh_node *)malloc(sizeof(t_linear_bvh_node)
			* bvh_build->n_nodes);
	if (!linear_bvh->bvh_nodes)
		return (free(linear_bvh), NULL);
	linear_bvh->objects = objects;
	linear_bvh->length = objects->size;
	offset = 0;
	_flatten_bvh(linear_bvh, bvh_build->root, &offset);
	return (linear_bvh);
}
