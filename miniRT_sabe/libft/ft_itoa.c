/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:32:03 by sabe              #+#    #+#             */
/*   Updated: 2025/02/19 18:48:30 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	int	digit;

	digit = 0;
	if (n <= 0)
		digit++;
	while (n != 0)
	{
		digit++;
		n /= 10;
	}
	return (digit);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-1 * n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	int		digit;
	char	*ptr;

	digit = count_digit(n);
	ptr = (char *)malloc(sizeof(char) * (digit + 1));
	if (!ptr)
		return (NULL);
	ptr[digit--] = '\0';
	if (n == 0)
		ptr[0] = '0';
	if (n < 0)
		ptr[0] = '-';
	while (n != 0)
	{
		ptr[digit--] = '0' + ft_abs((n % 10));
		n /= 10;
	}
	return (ptr);
}
