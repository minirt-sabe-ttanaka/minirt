/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:44:48 by sabe              #+#    #+#             */
/*   Updated: 2025/02/18 14:50:28 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			count;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	count = 0;
	while (count < n)
	{
		if (ptr1[count] != ptr2[count])
			return (ptr1[count] - ptr2[count]);
		count++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	buf2[] = "\0abc\0de";
// 	char	buf3[] = "\0abcdef";

// 	char buf1[] = "\0abc\0de"; /* 途中に空文字のある文字列 */
// 	if (memcmp(buf1, buf2, 7) == 0)
// 		printf("buf1 = buf2\n");
// 	else
// 		printf("buf1 != buf2\n");
// 	if (memcmp(buf1, buf3, 7) == 0)
// 		printf("buf1 = buf3\n");
// 	else
// 		printf("buf1 != buf3\n");
// 	return (0);
// }
