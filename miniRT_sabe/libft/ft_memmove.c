/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:23:44 by sabe              #+#    #+#             */
/*   Updated: 2025/02/18 15:33:20 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*ptr;
	char	*ptr_src;
	size_t	count;

	count = 0;
	ptr = (char *)dst;
	ptr_src = (char *)src;
	if (dst < src)
	{
		while (count < n)
		{
			ptr[count] = ptr_src[count];
			count++;
		}
	}
	else
	{
		while (count < n)
		{
			ptr[n - count - 1] = ptr_src[n - count - 1];
			count++;
		}
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// #define BUF_SIZE 16

// int	main(void)
// {
// 	char	buf1[BUF_SIZE];
// 	char	buf2[BUF_SIZE];

// 	// 変数定義
// 	// 変数初期化
// 	memset(buf1, '\0', BUF_SIZE);
// 	memset(buf2, '\0', BUF_SIZE);
// 	// メモリ領域を特定の文字で埋める
// 	memset(buf1, 'b', 4); // buf1の最初の4バイトをaにする
// 	memset(buf1, 'a', 2); // buf1の最初の2バイトをbにする
// 	// 配列の内容を表示
// 	printf("配列の要素を表示(コピー前)。\n");
// 	printf("buf1:%s\n", buf1);
// 	printf("buf2:%s\n", buf2);
// 	// メモリを上書きする
// 	ft_memmove(buf2, buf1, 3);         // buf1の先頭3バイトをbuf2に上書きする
// 	ft_memmove(&buf1[2], &buf1[0], 3); // buf1の先頭3バイトをbuf1の3バイト目に上書きする
// 	// 配列の内容を表示
// 	printf("配列の要素を表示(コピー後)。\n");
// 	printf("buf1:%s\n", buf1);
// 	printf("buf2:%s\n", buf2);
// 	return (0);
// }
