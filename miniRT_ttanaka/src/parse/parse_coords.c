/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:43 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:22:44 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/parse.h"

bool	parse_coords_format(char *s, t_color3 *point);

bool	parse_coords_format(char *s, t_color3 *point)
{
	char	**splitted_data;
	int		i;

	splitted_data = ft_split(s, ',');
	if (!splitted_data)
		return (false);
	if (ft_strarr_len(splitted_data) != 3)
	{
		free_splited_data(splitted_data);
		return (false);
	}
	i = 0;
	while (i < 3)
	{
		if (parse_double(splitted_data[i], &(point->v[i])) == false)
		{
			free_splited_data(splitted_data);
			return (false);
		}
		i++;
	}
	free_splited_data(splitted_data);
	return (true);
}
