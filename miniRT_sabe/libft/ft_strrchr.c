/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:29:53 by sabe              #+#    #+#             */
/*   Updated: 2025/02/18 15:43:15 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		count;
	char	ch;

	count = (int)ft_strlen((char *)s);
	ch = (char)c;
	while (count >= 0)
	{
		if (s[count] == ch)
			return ((char *)(s + count));
		count--;
	}
	return (NULL);
}

// #include <assert.h>
// #include <stdio.h>
// #include <bsd/string.h>

// /*
//  * 自作の ft_strrchr 関数のプロトタイプ
//  * ft_strrchr は、文字列 s 内で最後に現れる文字 c のポインタを返します。
//  * 見つからなければ NULL を返すものとします。
//  */

// int	main(void)
// {
// 	const char	*str = "Hello, world!";
// 	char		*p;
// 	const char	*empty = "";
// 	const char	*str2 = "banana";

// 	// テストケース1: 文字列中に複数回出現する文字の最後の出現を検索
// 	// "Hello, world!" 内の 'o' は、インデックス 4 と 8 に現れます。
// 	// 最後の 'o' はインデックス 8 にあるはずです。
// 	p = ft_strrchr(str, 'o');
// 	printf("テスト1: 検索対象 'o' → 結果: %s\n", p);
// 	assert(p != NULL);
// 	assert(*p == 'o');
// 	assert((size_t)(p - str) == 8);
// 	// テストケース2: 文字列の先頭にある文字を検索
// 	// 文字 'H' は先頭にのみ存在するため、返り値は str と同じになるはずです。
// 	p = ft_strrchr(str, 'H');
// 	printf("テスト2: 検索対象 'H' → 結果: %s\n", p);
// 	assert(p == str);
// 	// テストケース3: 存在しない文字を検索
// 	p = ft_strrchr(str, 'z');
// 	printf("テスト3: 検索対象 'z' → 結果: %p\n", (void *)p);
// 	assert(p == NULL);
// 	// テストケース4: ヌル文字 '\0' を検索
// 	// ヌル文字の検索は、文字列の末尾（ヌル文字のアドレス）を返す仕様です。
// 	p = ft_strrchr(str, '\0');
// 	printf("テスト4: 検索対象 '\\0' → 結果: %p\n", (void *)p);
// 	assert(p != NULL);
// 	assert(p == str + strlen(str));
// 	// テストケース5: 空文字列での検索
// 	p = ft_strrchr(empty, 'a');
// 	printf("テスト5-1: 空文字列で 'a' を検索 → 結果: %p\n", (void *)p);
// 	assert(p == NULL);
// 	p = ft_strrchr(empty, '\0');
// 	printf("テスト5-2: 空文字列で '\\0' を検索 → 結果: %p\n", (void *)p);
// 	// 空文字列の場合、ヌル文字は文字列の先頭（アドレスが empty と同じ）にあります。
// 	assert(p == empty);
// 	// テストケース6: 同じ文字が複数回出現する場合、最後の出現位置を返す
// 	p = ft_strrchr(str2, 'a');
// 	printf("テスト6: \"banana\" で 'a' を検索 → 結果: %s\n", p);
// 	// "banana" では、'a' はインデックス 1, 3, 5 に現れるので、最後はインデックス 5 です。
// 	assert(p != NULL);
// 	assert((size_t)(p - str2) == 5);
// 	printf("すべてのテストをパスしました。\n");
// 	return (0);
// }
