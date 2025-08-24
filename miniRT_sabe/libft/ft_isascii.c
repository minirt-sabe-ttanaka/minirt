/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:11:46 by sabe              #+#    #+#             */
/*   Updated: 2025/02/09 15:20:40 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (1);
	else
		return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d\n", ft_isascii('a') == 1);
// 	printf("%d\n", ft_isascii('-') == 1);
// 	printf("%d\n", ft_isascii('	') == 1);
// 	printf("%d\n", ft_isascii('\n') == 1);
// }
