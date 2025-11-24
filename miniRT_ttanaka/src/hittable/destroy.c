/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:24:04 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:24:05 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/hittable.h"

static void	destroy_bvh_build_node_recursive(t_bvh_build_node *node);
void		destroy_bvh_build(t_bvh_build *bvh_build);
void		destroy_hittable_lst(t_hittable_lst *lst);
void		destroy_linear_bvh(t_linear_bvh *bvh);

static void	destroy_bvh_build_node_recursive(t_bvh_build_node *node)
{
	if (!node)
		return ;
	destroy_bvh_build_node_recursive(node->left);
	destroy_bvh_build_node_recursive(node->right);
	free(node);
}

void	destroy_bvh_build(t_bvh_build *bvh_build)
{
	t_bvh_build_node	*root;

	if (!bvh_build)
		return ;
	root = bvh_build->root;
	destroy_bvh_build_node_recursive(root);
	free(bvh_build);
}

void	destroy_hittable_lst(t_hittable_lst *lst)
{
	int	i;

    if (!lst)
        return;
	i = 0;
	while (i < lst->size)
	{
        if (lst->objects[i].vtable && lst->objects[i].vtable->destroy)
    		lst->objects[i].vtable->destroy((void *)lst->objects[i].object);
		i++;
	}
	free(lst->objects);
	free(lst);
}

void	destroy_linear_bvh(t_linear_bvh *bvh)
{
    if (!bvh)
        return;
	free(bvh->bvh_nodes);
	destroy_hittable_lst(bvh->objects);
    free(bvh);
}
