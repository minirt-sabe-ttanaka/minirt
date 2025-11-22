#include "parse.h"

static uint8_t	a2uint8(char *s, bool *success);
bool			parse_color_format(char *s, t_color3 *color);

static uint8_t	a2uint8(char *s, bool *success)
{
	unsigned int	val;
	size_t			s_len;

	*success = false;
	s_len = ft_strlen(s);
	if (s_len > 3 || s_len == 0)
		return (0);
	val = 0;
	while (*s && ft_isdigit(*s))
		val = val * 10 + (*s++ - '0');
	if (*s)
		return (0);
	if (val > 255)
		return (0);
	*success = true;
	return ((uint8_t)val);
}

bool	parse_color_format(char *s, t_color3 *color)
{
	char	**splitted_data;
	bool	is_success[3];

	splitted_data = ft_split(s, ',');
	if (!splitted_data)
		return (false);
	if (ft_strarr_len(splitted_data) != 3)
	{
		free_splited_data(splitted_data);
		return (false);
	}
	color->r = a2uint8(splitted_data[0], &(is_success[0])) / 255.0;
	color->g = a2uint8(splitted_data[1], &(is_success[1])) / 255.0;
	color->b = a2uint8(splitted_data[2], &(is_success[2])) / 255.0;
	free_splited_data(splitted_data);
	if (is_success[0] == false || is_success[1] == false
		|| is_success[2] == false)
		return (false);
	return (true);
}
