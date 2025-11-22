/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:29:12 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/22 02:55:11 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;

	if (!s)
		return ;
	c = (unsigned char *)s;
	while (n)
	{
		*c++ = 0;
		n--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_cpy;
	char	*src_cpy;
	size_t	i;

	if (!dst || !src)
		return (dst);
	dst_cpy = (char *)dst;
	src_cpy = (char *)src;
	if (!len || dst == src)
		return (dst);
	if (dst_cpy < src_cpy)
	{
		i = 0;
		while (i < len)
		{
			dst_cpy[i] = src_cpy[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			dst_cpy[len] = src_cpy[len];
	}
	return (dst);
}

t_buf_node	*create_buf_node(int fd)
{
	t_buf_node	*newnode;
	t_buf		*buf;

	newnode = malloc(sizeof(t_buf_node));
	if (!newnode)
		return (NULL);
	newnode->fd = fd;
	newnode->next = NULL;
	buf = &(newnode->buffer);
	ft_bzero(buf->buf, BUFFER_SIZE);
	buf->bufp = buf->buf;
	buf->bufsiz = 0;
	return (newnode);
}

void	init_buf_node(t_buf_node *node, int fd)
{
	node->fd = fd;
	node->next = NULL;
	ft_bzero(node->buffer.buf, BUFFER_SIZE);
	node->buffer.bufp = node->buffer.buf;
	node->buffer.bufsiz = 0;
}

char	*adjust_string(t_string *res)
{
	char	*final_res;

	if (res->len == 0)
	{
		if (res->str)
			free(res->str);
		return (NULL);
	}
	if (res->len > 0 && res->str[res->len - 1] == '\n')
	{
		res->str[res->len - 1] = 0;
		res->len -= 1;
	}
	final_res = (char *)malloc(sizeof(char) * (res->len) + 1);
	if (!final_res)
	{
		if (res->str)
			free(res->str);
		return (NULL);
	}
	ft_memmove(final_res, res->str, res->len);
	final_res[res->len] = '\0';
	if (res->str)
		free(res->str);
	return (final_res);
}
