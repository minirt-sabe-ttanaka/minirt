/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:08:04 by sabe              #+#    #+#             */
/*   Updated: 2025/02/19 16:56:54 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_check(char const c, char const *set)
{
	size_t	count;

	count = 0;
	while (set[count] != '\0')
	{
		if (c == set[count])
			return (1);
		count++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;
	size_t	count;

	if (!s1)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	start = 0;
	count = 0;
	end = ft_strlen(s1) - 1;
	while (str_check(s1[start], set) && s1[start] != '\0')
		start++;
	while (str_check(s1[end], set) && start < end)
		end--;
	ptr = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!ptr)
		return (NULL);
	while (start <= end)
		ptr[count++] = s1[start++];
	ptr[count] = '\0';
	return (ptr);
}
