/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:21:02 by sabe              #+#    #+#             */
/*   Updated: 2025/02/09 15:23:49 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (32 <= c && c <= 126)
		return (1);
	else
		return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d\n", ft_isprint('a') == 1);
// 	printf("%d\n", ft_isprint('-') == 1);
// 	printf("%d\n", ft_isprint('\n') == 0);
// 	printf("%d\n", ft_isprint('\0') == 0);
// }
