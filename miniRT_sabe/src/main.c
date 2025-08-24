/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesouichirou <abesouichirou@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 22:30:48 by abesouichir       #+#    #+#             */
/*   Updated: 2025/08/22 14:58:42 by abesouichir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color3 ray_color(const t_ray r, const t_hittable_lst *lst, int depth) {
  t_hit_record rec;
  if (depth <= 0) {
    return (t_color3){0, 0, 0}; // 深さが0以下なら黒を返す
  }
  if (hit_hittable_lst(lst, &r, 0.001, DBL_MAX, &rec))
  {
    t_ray scattered;
    t_color3 attenuation;
    if (rec.mat.vtable->scatter(rec.mat.object, &r, &rec, &attenuation, &scattered))
    {
      return vec3_mul_v(attenuation, ray_color(scattered, lst, depth - 1));
    }
    return (t_color3){0, 0, 0}; // マテリアルが散乱しない場合は黒を返す
  }
  t_vec3 unit_direction = unit_vector(r.dir);
  double t = 0.5 * (unit_direction.y + 1.0);
  return (t_color3){
    (1.0 - t) * 1.0 + t * 0.5,
    (1.0 - t) * 1.0 + t * 0.7,
    (1.0 - t) * 1.0 + t * 1.0
  };
}

static double clamp_double(double x, double lo, double hi) {
  if (x < lo) return lo;
  if (x > hi) return hi;
  return x;
}

int main(int argc, char **argv)
{
  t_world *w;
  int width;
  int height;

  (void)argc;
  (void)argv;
  const double aspect_ratio = 16.0 / 9.0;
  width = 960;
  height = (int)(width / aspect_ratio + 0.5);

  w = ft_calloc(1, sizeof(t_world));
  if (!w) return (1);
  w->screen_width = width;
  w->screen_height = height;

  double viewport_height = 2.0;
  double viewport_width = aspect_ratio * viewport_height;
  double focal_length = 1.0;
  t_point3 origin = (t_point3){0, 0, 0};
  t_vec3 horizontal = (t_vec3){viewport_width, 0, 0};
  t_vec3 vertical = (t_vec3){0, viewport_height, 0};
  /* カメラは原点の前方 = -z にビューポートがある想定 */
  t_vec3 lower_left_corner = (t_vec3){
    origin.x - horizontal.x / 2.0 - vertical.x / 2.0,
    origin.y - horizontal.y / 2.0 - vertical.y / 2.0,
    origin.z - focal_length
  };
  t_camera camera = camera_create(origin, horizontal, vertical, lower_left_corner);
  const int max_depth = 10;
  const int samples_per_pixel = 10;

  t_hittable_lst lst;
  hittable_lst_init(&lst);
  t_material pink_lambertian = *lambertian_new((t_color3){0.8, 0.3, 0.3});
  t_material green_lambertian = *lambertian_new((t_color3){0.8, 0.8, 0.0});
  t_material blue_metal = *metal_new((t_color3){0.2, 0.2, 0.8}, 0.0);
  // t_material red_metal = *metal_new((t_color3){0.8, 0.2, 0.2}, 0.8);
  t_material white_dielectric = *dielectric_new((t_color3){1.0, 1.0, 1.0}, 1.5);
  sphere_create(&lst, (t_vec3){0, 0, -1}, 0.5, pink_lambertian);
  sphere_create(&lst, (t_vec3){0, -100.5, -1}, 100, green_lambertian);
  sphere_create(&lst, (t_vec3){1, 0, -1}, 0.5, blue_metal);
  sphere_create(&lst, (t_vec3){-1, 0, -1}, 0.5, white_dielectric);

  w->mlx = mlx_init();
  w->win = mlx_new_window(w->mlx, width, height, "minirt");

  w->img.img = mlx_new_image(w->mlx, width, height);

  /* mlx_get_data_addr に渡すのは image pointer（＝ w->img.img） */
  w->img.addr = mlx_get_data_addr(w->img.img,
                                 &w->img.bits_per_pixel,
                                 &w->img.line_length,
                                 &w->img.endian);
  w->img.width = width;
  w->img.height = height;

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      t_color3 pixel_color = vec3_create(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        double u = ((double)x + rand_double(0.0, 1.0)) / (width - 1);
        double v = ((double)(height - y - 1) + rand_double(0.0, 1.0)) / (height - 1);
        t_ray r = camera_get_ray(&camera, u, v);
        pixel_color =vec3_add(pixel_color, ray_color(r, &lst, max_depth));
      }
      pixel_color = vec3_mul_s(pixel_color, 1.0 / samples_per_pixel);
      pixel_color = vec3_sqrt(pixel_color);
      int ir = (int)(255.999 * clamp_double(pixel_color.x, 0.0, 0.999));
      int ig = (int)(255.999 * clamp_double(pixel_color.y, 0.0, 0.999));
      int ib = (int)(255.999 * clamp_double(pixel_color.z, 0.0, 0.999));
      my_mlx_pixel_put(&w->img, x, y, (ir << 16) | (ig << 8) | ib);
    }
    printf("progress: %d%%\r", (int)((double)y / (height - 1) * 100));
    fflush(stdout);
  }
  printf("progress: 100%%\n");

  mlx_put_image_to_window(w->mlx, w->win, w->img.img, 0, 0);
  mlx_loop(w->mlx);

  mlx_destroy_image(w->mlx, w->img.img);
  mlx_destroy_window(w->mlx, w->win);
  free(w);
  return (0);
}