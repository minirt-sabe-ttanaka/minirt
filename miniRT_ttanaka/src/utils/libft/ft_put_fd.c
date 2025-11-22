/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:14:01 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/11 20:18:20 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/libft.h"

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_puterr_fd(char *s);
void	ft_putendl_fd(char *s, int fd);

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_puterr_fd(char *s)
{
	if (!s)
		return ;
	write(STDERR_FILENO, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
