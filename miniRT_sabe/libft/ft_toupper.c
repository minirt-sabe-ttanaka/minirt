/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:06:16 by sabe              #+#    #+#             */
/*   Updated: 2025/02/09 18:09:05 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c - 32);
	else
		return (c);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%c\n", ft_toupper('a'));
// 	printf("%c\n", ft_toupper('z'));
// 	printf("%c\n", ft_toupper('A'));
// 	printf("%c\n", ft_toupper('-'));
// }
