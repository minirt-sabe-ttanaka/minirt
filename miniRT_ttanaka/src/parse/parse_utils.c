/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:28 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 23:20:10 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/parse.h"

# define LINE_TOO_LONG "line too long\n"

static bool	parse_line_sections(char **splitted_data, t_scene *scene);
static bool	is_space_line(char *s);
static bool	parse_single_line(char *line, t_scene *scene);
bool		read_lines_loop(int fd, t_scene *scene);

static void replace_whitespace_with_space(char *line)
{
    while (*line)
    {
        if (ft_isspace(*line))
            *line = ' ';
        line++;
    }
}

static bool	parse_line_sections(char **splitted_data, t_scene *scene)
{
	if (!splitted_data[0])
		return (true);
	if (ft_strcmp(splitted_data[0], "A") == 0)
		return (set_ambient(splitted_data, scene));
	if (ft_strcmp(splitted_data[0], "C") == 0)
		return (set_camera(splitted_data, scene));
	if (ft_strcmp(splitted_data[0], "L") == 0)
		return (set_light(splitted_data, scene));
	if (ft_strcmp(splitted_data[0], "sp") == 0)
		return (set_sphere(splitted_data, scene));
	if (ft_strcmp(splitted_data[0], "pl") == 0)
		return (set_plane(splitted_data, scene));
	if (ft_strcmp(splitted_data[0], "cy") == 0)
		return (set_cylinder(splitted_data, scene));
	if (ft_strcmp(splitted_data[0], "tr") == 0)
		return (set_triangle(splitted_data, scene));
	return (false);
}

static bool	is_space_line(char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	if (!(*s))
		return (true);
	else
		return (false);
}

static bool is_comment(char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	if (*s && *s == '#')
		return (true);
	return (false);
}

static bool	parse_single_line(char *line, t_scene *scene)
{
	char	**splitted_data;
	bool	result;

	if (is_space_line(line))
		return (true);
	if (is_comment(line))
		return (true);
	replace_whitespace_with_space(line);
	splitted_data = ft_split(line, ' ');
	if (!splitted_data)
		return (false);
	result = parse_line_sections(splitted_data, scene);
	free_splited_data(splitted_data);
	return (result);
}

bool	read_lines_loop(int fd, t_scene *scene)
{
	char *line;
	bool gnl_err;

	line = get_next_line(fd, &gnl_err);
	while (line)
	{
		if (parse_single_line(line, scene) == false)
		{
			notify_err_line_content(line);
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd, &gnl_err);
	}
	return (!gnl_err);
}
