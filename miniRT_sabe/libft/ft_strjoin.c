/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:56:39 by sabe              #+#    #+#             */
/*   Updated: 2025/02/19 16:10:54 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	count1;
	size_t	count2;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	count1 = 0;
	count2 = 0;
	while (s1[count1] != '\0')
	{
		ptr[count1] = s1[count1];
		count1++;
	}
	while (s2[count2] != '\0')
	{
		ptr[count1 + count2] = s2[count2];
		count2++;
	}
	ptr[count1 + count2] = '\0';
	return (ptr);
}
