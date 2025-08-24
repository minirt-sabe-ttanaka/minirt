/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:12:41 by sabe              #+#    #+#             */
/*   Updated: 2025/02/20 20:16:51 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*lst_cp;

	size = 0;
	lst_cp = lst;
	if (!lst)
		return (0);
	while (lst_cp->next != NULL)
	{
		size++;
		lst_cp = lst_cp->next;
	}
	return (size + 1);
}
