/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:31 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 18:46:07 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/parse.h"

bool		check_extension(char *path);
bool		parse_file(char *path, t_scene *scene);
bool		create_scene(char *path, t_scene *scene);

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

static bool	init_hittable_lsts(t_scene *scene)
{
	t_hittable_lst	*objects;
	t_hittable_lst	*lights;

	objects = (t_hittable_lst *)malloc(sizeof(t_hittable_lst));
	lights = (t_hittable_lst *)malloc(sizeof(t_hittable_lst));
	if (!objects || !lights)
	{
		free(objects);
		free(lights);
		return (false);
	}
	hittable_lst_init(objects);
	hittable_lst_init(lights);
	scene->objects = objects;
	scene->light_group = create_hittable_lst(lights);
	return (true);
}

bool	create_scene(char *path, t_scene *scene)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	if (read_lines_loop(fd, scene) == false
		|| scene->camera_initialized == false)
	{
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
	if (init_hittable_lsts(scene) == false)
		return (false);
	if (create_scene(path, scene) == false)
	{
		destroy_hittable_lst(scene->objects);
		return (false);
	}
	if ((scene->objects->size) == 0)
	{
		scene->bvh = NULL;
		return (true);
	}
	if (convert_lst_2_bvh(scene->objects, &scene->bvh) == false)
	{
		destroy_hittable_lst(scene->objects);
		return (false);
	}
	return (true);
}
