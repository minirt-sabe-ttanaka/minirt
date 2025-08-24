/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:13:43 by sabe              #+#    #+#             */
/*   Updated: 2025/02/18 15:42:09 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;
	char	ch;

	count = 0;
	ch = (char)c;
	while (1)
	{
		if (s[count] == ch)
			return ((char *)(s + count));
		else if (s[count] == '\0')
			return (NULL);
		count++;
	}
}

// #include <assert.h>
// #include <stdio.h>
// #include <string.h>

// /*
//  * 自作の ft_strchr 関数のプロトタイプ
//  * ※ 標準関数 strchr と同様に、文字列 s 内で最初に現れる文字 c のポインタを返し、
//  *    見つからなければ NULL を返すものとします。
//  */
// char	*ft_strchr(const char *s, int c);

// int	main(void)
// {
// 	const char	*str = "Hello, world!";
// 	char		*p;
// 	const char	*empty = "";
// 	const char	*str2 = "banana";

// 	// テストケース1: 文字列中に存在する文字を検索（途中の文字）
// 	p = ft_strchr(str, 'w');
// 	printf("テスト1: 検索対象 'w' → 結果: %s\n", p);
// 	assert(p != NULL);
// 	assert(*p == 'w');
// 	// "Hello, world!" において、'w' は 7 番目（0オリジン: index 7）に現れるはず
// 	assert(p - str == 7);
// 	// テストケース2: 文字列の先頭にある文字を検索
// 	p = ft_strchr(str, 'H');
// 	printf("テスト2: 検索対象 'H' → 結果: %s\n", p);
// 	assert(p == str);
// 	// テストケース3: 存在しない文字を検索
// 	p = ft_strchr(str, 'z');
// 	printf("テスト3: 検索対象 'z' → 結果: %p\n", (void *)p);
// 	assert(p == NULL);
// 	// テストケース4: ヌル文字 '\0' を検索（文字列末尾のヌル文字へのポインタが返る）
// 	p = ft_strchr(str, '\0');
// 	printf("テスト4: 検索対象 '\\0' → 結果: %p\n", (void *)p);
// 	assert(p != NULL);
// 	assert(p == str + strlen(str));
// 	// テストケース5: 空文字列での検索
// 	p = ft_strchr(empty, 'a');
// 	printf("テスト5-1: 空文字列で 'a' を検索 → 結果: %p\n", (void *)p);
// 	assert(p == NULL);
// 	p = ft_strchr(empty, '\0');
// 	printf("テスト5-2: 空文字列で '\\0' を検索 → 結果: %p\n", (void *)p);
// 	// 空文字列の場合、ヌル文字は文字列の先頭にあるので、empty と同じアドレスが返る
// 	assert(p == empty);
// 	// テストケース6: 同じ文字が複数回現れる場合は最初のものが返る
// 	p = ft_strchr(str2, 'a');
// 	printf("テスト6: \"banana\" で 'a' を検索 → 結果: %s\n", p);
// 	assert(p != NULL);
// 	// "banana" では最初の 'a' はインデックス 1 にあるはず
// 	assert(p - str2 == 1);
// 	printf("すべてのテストをパスしました。\n");
// 	return (0);
// }
