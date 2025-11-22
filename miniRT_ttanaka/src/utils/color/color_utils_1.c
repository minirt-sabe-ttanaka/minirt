#include "utils/color.h"

t_color3	color_scale(t_color3 c, double s);
t_color3	color_add(t_color3 a, t_color3 b);
int			tcolor2rgb(t_color3 c);
int			create_rgb(int r, int g, int b);
int			interpolate_color(int c_start, int c_end, double t);

t_color3	color_scale(t_color3 c, double s)
{
	return (color_init(c.r * s, c.g * s, c.b * s));
}

t_color3	color_add(t_color3 a, t_color3 b)
{
	return (color_init(a.r + b.r, a.g + b.g, a.b + b.b));
}

int	tcolor2rgb(t_color3 c)
{
	return ((int)(c.r * 255.999) << 16 | (int)(c.g * 255.999) << 8 | (int)(c.b
			* 255.999));
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	interpolate_color(int c_start, int c_end, double t)
{
	int	r_interp;
	int	g_interp;
	int	b_interp;

	r_interp = round((1.0 - t) * get_r(c_start) + t * get_r(c_end));
	g_interp = round((1.0 - t) * get_g(c_start) + t * get_g(c_end));
	b_interp = round((1.0 - t) * get_b(c_start) + t * get_b(c_end));
	r_interp = ft_max(r_interp, 0);
	g_interp = ft_max(g_interp, 0);
	b_interp = ft_max(b_interp, 0);
	r_interp = ft_min(r_interp, 255);
	g_interp = ft_min(g_interp, 255);
	b_interp = ft_min(b_interp, 255);
	return ((r_interp << 16) | (g_interp << 8) | (b_interp));
}
