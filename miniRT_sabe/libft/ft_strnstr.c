/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:51:42 by sabe              #+#    #+#             */
/*   Updated: 2025/02/18 16:46:30 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	count1;
	size_t	count2;

	if (needle[0] == '\0')
		return ((char *)haystack);
	count1 = 0;
	while (haystack[count1] != '\0')
	{
		count2 = 0;
		while (needle[count2] != '\0')
		{
			if (count1 + count2 >= len)
				return (NULL);
			if (haystack[count1 + count2] != needle[count2])
				break ;
			count2++;
		}
		if (needle[count2] == '\0')
			return ((char *)(haystack + count1));
		count1++;
	}
	return (NULL);
}

// #include <stdbool.h>
// #undef NDEBUG
// #include <assert.h>
// #include <string.h>

// const char	*haystack = "Lorem ipsum dolor sit amet";

// static void	test(const char *haystack, const char *needle, size_t len,
// bool res)
// {
// 	char	*str;

// 	if (len == 0)
// 		len = strlen(haystack);
// 	str = ft_strnstr(haystack, needle, len);
// 	assert(res == (str != NULL));
// }

// int	main(void)
// {
// 	test(haystack, "Lorem", 0, true);
// 	test(haystack, "Sea Otters", 0, false);
// 	test(haystack, "", 0, true);
// 	test(haystack, "Lorem ipsum dolor sit amet, but bigger", 0, false);
// 	test(haystack, haystack, 0, true);
// 	test(haystack, "amet", 0, true);
// 	test(haystack, "dolor", 5, false);
// }
