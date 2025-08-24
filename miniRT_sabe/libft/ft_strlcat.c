/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:36:12 by sabe              #+#    #+#             */
/*   Updated: 2025/02/18 16:13:08 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	count;

	count = 0;
	dst_len = ft_strlen(dst);
	if (dstsize == 0)
		return (dstsize + ft_strlen(src));
	while (count + dst_len + 1 < dstsize && src[count] != '\0')
	{
		dst[dst_len + count] = src[count];
		count++;
	}
	dst[dst_len + count] = '\0';
	if (dst_len < dstsize)
		return (dst_len + ft_strlen(src));
	else
		return (dstsize + ft_strlen(src));
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	dest[30];
// 	char	*src;

// 	memset(dest, 0, 30);
// 	src = (char *)"AAAAAAAAA";
// 	dest[0] = 'B';
// 	printf("%zu\n", ft_strlcat(dest, src, -1));
// 	printf("%s\n", dest);
// 	return (0);
// }
