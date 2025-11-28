/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:22:32 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 23:35:30 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/parse.h"

bool	set_ambient(char **splitted_data, t_scene *scene);
bool	set_camera(char **splitted_data, t_scene *scene);
bool	set_light(char **splitted_data, t_scene *scene);

bool	set_ambient(char **splitted_data, t_scene *scene) {
  if (scene->ambient_initialized == true)
    return (false);
  if (ft_strarr_len(splitted_data) != 3)
    return (false);
  if (parse_double(splitted_data[1], &(scene->ambient.ratio)) == false)
    return (false);
  if (scene->ambient.ratio < 0.0 || 1.0 < scene->ambient.ratio)
    return (false);
  if (parse_color_format(splitted_data[2], &(scene->ambient.color)) == false)
    return (false);
  scene->ambient_initialized = true;
  return (true);
}

bool	set_camera(char **splitted_data, t_scene *scene) {
  t_camera_config config;

  if (scene->camera_initialized == true)
    return (false);
  if (ft_strarr_len(splitted_data) != 4)
    return (false);
  if (parse_coords_format(splitted_data[1], &(config.look_from)) == false)
    return (false);
  if (parse_coords_format(splitted_data[2], &(config.look_to)) == false)
    return (false);
  if (fabs(vec_norm_squared(config.look_to) - 1.0) > EPS)
    return (false);
  if (parse_double(splitted_data[3], &(config.fov)) == false)
    return (false);
  if (config.fov < 0.0 || 180.0 < config.fov)
    return (false);
  config.aspect_ratio =
      (double)scene->screen_width / (double)scene->screen_height;
  config.vup = vec_init(0, 1, 0);
  if (fabs(config.look_to.x) < EPS && fabs(config.look_to.z) < EPS)
    config.vup = vec_init(1, 0, 0);
  camera_init(&(scene->camera), &config);
  scene->camera_initialized = true;
  return (true);
}

bool	set_light(char **splitted_data, t_scene *scene) {
  if (scene->light_initialized == true)
    return (false);
    
  if (ft_strarr_len(splitted_data) != 4)
    return (false);
  if (parse_coords_format(splitted_data[1], &(scene->light.origin)) == false)
    return (false);
  if (parse_double(splitted_data[2], &(scene->light.ratio)) == false)
    return (false);
  if (scene->light.ratio < 0.0 || 1.0 < scene->light.ratio)
    return (false);
  if (parse_color_format(splitted_data[3], &(scene->light.color)) == false)
    return (false);
  scene->light_initialized = true;
  return (true);
}
