/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:31:55 by sabe              #+#    #+#             */
/*   Updated: 2025/02/09 16:08:25 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t n)
{
	size_t	count;
	char	*ptr;

	count = 0;
	ptr = (char *)buf;
	while (count < n)
	{
		ptr[count] = ch;
		count++;
	}
	return (buf);
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
// 	ft_memset(buf1, '\0', BUF_SIZE);
// 	ft_memset(buf2, '\0', BUF_SIZE);
// 	// 配列の内容を表示
// 	printf("初期化後の配列の要素を表示。\n");
// 	printf("buf1:%s\n", buf1);
// 	printf("buf2:%s\n", buf2);
// 	// メモリ領域を特定の文字で埋める
// 	ft_memset(buf1, 'a', 4); // buf1の最初の4バイトをaにする
// 	ft_memset(buf1, 'b', 2); // buf1の最初の2バイトをbにする
// 	ft_memset(buf2, 'c', 3); // buf2の最初の3バイトをcにする
// 	// 配列の内容を表示
// 	printf("配列の要素を表示。\n");
// 	printf("buf1:%s\n", buf1);
// 	printf("buf2:%s\n", buf2);
// 	return (0);
// }
