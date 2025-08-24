/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:01:44 by sabe              #+#    #+#             */
/*   Updated: 2025/02/09 16:18:58 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptr;
	char	*ptr_src;
	size_t	count;

	count = 0;
	ptr = (char *)dst;
	ptr_src = (char *)src;
	while (count < n)
	{
		ptr[count] = ptr_src[count];
		count++;
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
// 	// メモリをコピーする
// 	ft_memcpy(buf2, buf1, 3); // buf1の先頭3バイトをbuf2にコピーする
// 	// 配列の内容を表示
// 	printf("配列の要素を表示(コピー後)。\n");
// 	printf("buf1:%s\n", buf1);
// 	printf("buf2:%s\n", buf2);
// 	return (0);
// }
