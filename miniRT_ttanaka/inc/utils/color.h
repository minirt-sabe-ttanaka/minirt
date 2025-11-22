#ifndef COLOR_H
# define COLOR_H

# include "ft_math.h"
# include "vector.h"
# include <math.h>

typedef t_vec3	t_color3;

t_color3		color_init(double r, double g, double b);
t_color3		rgb2color(u_int8_t r, u_int8_t g, u_int8_t b);
t_color3		color_scale(t_color3 c, double s);
t_color3		color_add(t_color3 a, t_color3 b);
int				tcolor2rgb(t_color3 c);
int				create_rgb(int r, int g, int b);
int				get_r(int rgb);
int				get_g(int rgb);
int				get_b(int rgb);
int				add_shade(int rgb, double shade_factor);
int				get_opposite(int rgb);
int				interpolate_color(int c_start, int c_end, double t);

#endif