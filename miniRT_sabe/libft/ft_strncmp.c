/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:21:50 by sabe              #+#    #+#             */
/*   Updated: 2025/02/18 14:46:53 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		if (s1[count] == '\0' && s2[count] == '\0')
			break ;
		if (s1[count] != s2[count])
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
//     char str[] = "ABC";
//     printf("ABC: ABD   = %d\n", strncmp(str, "ABD", 2));
//     printf("ABC: ABC   = %d\n", strncmp(str, "ABC", 2));
//     printf("ABC: AAA   = %d\n", strncmp(str, "AAA", 2));
//     printf("ABC: ABCD  = %d\n", strncmp(str, "ABCD", 2));
//     printf("ABC: AB    = %d\n", strncmp(str, "AB", 2));
//     printf("ABC: B     = %d\n", strncmp(str, "B", 2));
//     printf("ABC: A     = %d\n", strncmp(str, "A", 2));
//     return (0);
// }
