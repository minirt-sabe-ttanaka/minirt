/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:50:11 by sabe              #+#    #+#             */
/*   Updated: 2025/02/09 15:05:32 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d\n", ft_isdigit('0') == 1);
// 	printf("%d\n", ft_isdigit('9') == 1);
// 	printf("%d\n", ft_isdigit('5') == 1);
// 	printf("%d\n", ft_isdigit('-') == 0);
// }
