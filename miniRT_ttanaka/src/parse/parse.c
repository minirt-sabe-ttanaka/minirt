/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:31 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:22:32 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/parse.h"

bool	check_extension(char *path);
bool	parse_file(char *path, t_scene *scene);
bool	create_scene(char *path, t_scene *scene);

bool	check_extension(char *path)
{
	char	*dot_ptr;

	dot_ptr = ft_strrchr(path, '.');
	if (!dot_ptr || ft_strcmp(dot_ptr, ".rt"))
	{
		ft_puterr(ERRMSG_FILENAME);
		return (false);
	}
	return (true);
}

bool	create_scene(char *path, t_scene *scene)
{
	int				fd;
	t_hittable_lst	*hittable_lst;

	hittable_lst = (t_hittable_lst *)malloc(sizeof(t_hittable_lst));
	if (!hittable_lst)
		return (false);
	hittable_lst_init(hittable_lst);
	scene->objects = hittable_lst;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		destroy_hittable_lst(hittable_lst);
		return (false);
	}
	if (read_lines_loop(fd, scene) == false
		|| scene->camera_initialized == false)
	{
		destroy_hittable_lst(hittable_lst);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

bool	parse_file(char *path, t_scene *scene)
{
	if (check_extension(path) == false)
		return (false);
	if (create_scene(path, scene) == false)
		return (false);
	if ((scene->objects->size) == 0)
	{
		scene->bvh = NULL;
		return (true);
	}
	if (convert_lst_2_bvh(scene->objects, &scene->bvh) == false)
		return (false);
	return (true);
}
