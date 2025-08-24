/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:42 by sabe              #+#    #+#             */
/*   Updated: 2025/02/18 15:38:47 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	*ptr;
	unsigned char	ch;

	count = 0;
	ch = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (count < n)
	{
		if (ptr[count] == ch)
			return ((void *)(ptr + count));
		count++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*p;

// 	char str[] = "abcdef\0ghij"; /* 途中に空文字のある文字列 */
// 	p = memchr(str, 'h', 12);
// 	printf("検索文字は文字列の%d番目\n", p - str);
// 	return (0);
// }
