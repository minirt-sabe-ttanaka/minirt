/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:40:33 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/11 20:18:27 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/libft.h"

char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	char	c_cpy;

	if (!s)
		return (NULL);
	res = NULL;
	c_cpy = (char)c;
	while (*s)
	{
		if (*s == c_cpy)
			res = (char *)s;
		s++;
	}
	if (c_cpy == '\0')
		res = (char *)s;
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
