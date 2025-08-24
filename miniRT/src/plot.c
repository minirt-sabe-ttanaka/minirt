#include "minirt.h"

void my_mlx_pixel_put(t_world *world, int x, int y, int rgb);

void my_mlx_pixel_put(t_world *world, int x, int y, int rgb)
{
    char *dst;

    if (x < 0 || x >= world->screen_width || y < 0 || y >= world->screen_height)
        return;
    dst = world->addr + (y * world->line_length + x * (world->bits_per_pixel / 8));
    *(unsigned int*)dst = rgb;
}
