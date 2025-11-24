#include "engine/plot.h"

void my_mlx_pixel_put(t_scene *scene, int x, int y, int rgb)
{
    char *dst;

    if (x < 0 || x >= scene->screen_width || y < 0 || y >= scene->screen_height)
        return;
    dst = scene->addr + (y * scene->line_length + x * (scene->bits_per_pixel / 8));
    *(unsigned int*)dst = rgb;
}