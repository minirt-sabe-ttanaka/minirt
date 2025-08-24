/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:08:13 by sabe              #+#    #+#             */
/*   Updated: 2025/02/09 15:05:30 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1);
	else
		return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d\n", ft_isalpha('a') == 1);
// 	printf("%d\n", ft_isalpha('z') == 1);
// 	printf("%d\n", ft_isalpha('A') == 1);
// 	printf("%d\n", ft_isalpha('Z') == 1);
// 	printf("%d\n", ft_isalpha('g') == 1);
// 	printf("%d\n", ft_isalpha('-') == 0);
// }
