/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:31:59 by sabe              #+#    #+#             */
/*   Updated: 2025/02/18 15:51:46 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	if (dstsize == 0)
		return (ft_strlen(src));
	count = 0;
	while (count < dstsize - 1 && src[count] != '\0')
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	return (ft_strlen(src));
}

// #include <assert.h>
// #include <bsd/string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	buffer[50];
// 	size_t	ret;

// 	// テストケース1: 通常のコピー（十分なサイズのバッファ）
// 	memset(buffer, 0, sizeof(buffer));
// 	ret = ft_strlcpy(buffer, "Hello", sizeof(buffer));
// 	printf("テスト1: buffer = \"%s\", 戻り値 = %zu\n", buffer, ret);
// 	// 期待: bufferに"Hello"が入っており、戻り値はstrlen("Hello")と同じ
// 	assert(strcmp(buffer, "Hello") == 0);
// 	assert(ret == strlen("Hello"));
// 	// テストケース2: バッファサイズがソースの文字数+1にちょうど一致する場合
// 	memset(buffer, 0, sizeof(buffer));
// 	ret = ft_strlcpy(buffer, "World", 6); // "World"は5文字＋'\0'
// 	printf("テスト2: buffer = \"%s\", 戻り値 = %zu\n", buffer, ret);
// 	assert(strcmp(buffer, "World") == 0);
// 	assert(ret == strlen("World"));
// 	// テストケース3: バッファサイズが足りない場合（切り詰められる）
// 	memset(buffer, 0, sizeof(buffer));
// 	ret = ft_strlcpy(buffer, "Hello, World!", 6); // 最大5文字コピー＋'\0'
// 	printf("テスト3: buffer = \"%s\", 戻り値 = %zu\n", buffer, ret);
// 	// 期待: bufferには"Hello"が入る
// 	assert(strncmp(buffer, "Hello", 5) == 0);
// 	assert(buffer[5] == '\0');
// 	// 戻り値はソースの長さ (13) となるはず
// 	assert(ret == strlen("Hello, World!"));
// 	// テストケース4: dstsizeが0の場合（何もコピーせず、ソースの長さだけ返す）
// 	// bufferの内容は変更されないので、あらかじめ分かる値で埋めておく
// 	memset(buffer, 'X', sizeof(buffer));
// 	ret = ft_strlcpy(buffer, "Test", 0);
// 	printf("テスト4: dstsize=0の場合, 戻り値 = %zu\n", ret);
// 	assert(ret == strlen("Test"));
// 	// bufferの内容は変更されていない（ここでは検証が難しいので、戻り値のみチェック）
// 	// テストケース5: ソース文字列が空の場合
// 	memset(buffer, 0, sizeof(buffer));
// 	ret = ft_strlcpy(buffer, "", sizeof(buffer));
// 	printf("テスト5: buffer = \"%s\", 戻り値 = %zu\n", buffer, ret);
// 	assert(strcmp(buffer, "") == 0);
// 	assert(ret == 0);
// 	// ※ 注意:
// 	// NULLポインタを渡すケースは、標準のstrlcpyでは未定義動作となるため、
// 	// 自作関数でエラー処理（例: NULLチェック）を実装している場合にのみテストしてください。
// 	// ret = ft_strlcpy(NULL, "abc", 10);
// 	// ret = ft_strlcpy(NULL, "abc", 10);
// 	ret = ft_strlcpy(buffer, NULL, 10);
// 	printf("すべてのテストをパスしました。\n");
// 	return (0);
// }
