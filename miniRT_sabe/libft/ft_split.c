/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:02:56 by sabe              #+#    #+#             */
/*   Updated: 2025/02/19 18:23:36 by sabe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static size_t	word_length(const char *s, char c, size_t start)
{
	size_t	len;

	len = 0;
	while (s[start + len] && s[start + len] != c)
		len++;
	return (len);
}

static char	**free_split(char **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	*get_next_word(const char *s, char c, size_t *index)
{
	size_t	len;
	char	*word;
	size_t	j;

	len = word_length(s, c, *index);
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
		word[j++] = s[(*index)++];
	return (word);
}

char	**ft_split(const char *s, char c)
{
	size_t	index;
	size_t	i;
	char	**result;

	index = 0;
	i = 0;
	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	while (s[index])
	{
		if (s[index] != c)
		{
			result[i] = get_next_word(s, c, &index);
			if (!result[i])
				return (free_split(result, i));
			i++;
		}
		else
			index++;
	}
	result[i] = NULL;
	return (result);
}
