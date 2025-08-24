/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:00:01 by sabe              #+#    #+#             */
/*   Updated: 2025/02/09 15:25:46 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d\n", ft_isalnum('1') == 1);
// 	printf("%d\n", ft_isalnum('9') == 1);
// 	printf("%d\n", ft_isalnum('a') == 1);
// 	printf("%d\n", ft_isalnum('Z') == 1);
// 	printf("%d\n", ft_isalnum('-') == 0);
// }
