/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:48:24 by sabe              #+#    #+#             */
/*   Updated: 2025/02/20 19:46:08 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

static long int	ft_atol(const char *str)
{
	size_t		count;
	int			flag;
	long int	answer;

	count = 0;
	flag = 1;
	answer = 0;
	while (ft_isspace((int)str[count]))
		count++;
	if (str[count] == '-' || str[count] == '+')
	{
		if (str[count] == '-')
			flag = -1;
		count++;
	}
	while ('0' <= str[count] && str[count] <= '9')
	{
		answer *= 10;
		answer += str[count] - '0';
		count++;
	}
	return (answer * flag);
}

int	ft_atoi(const char *str)
{
	return ((int)ft_atol(str));
}
