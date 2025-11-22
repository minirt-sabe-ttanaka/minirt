#include "parse.h"

bool	is_double(char *s);
bool	parse_coords_format(char *s, t_color3 *point);

bool	is_double(char *s)
{
    bool has_digit;

    has_digit = false;
	if (*s == '+' || *s == '-')
		s++;
	while (*s && ft_isdigit(*s))
    {
		s++;
        has_digit = true;
    }
	if (*s && *s == '.')
		s++;
	while (*s && ft_isdigit(*s))
    {
		s++;
        has_digit = true;
    }
	if (*s)
		return (false);
	return (has_digit);
}

bool	parse_coords_format(char *s, t_color3 *point)
{
	char	**splitted_data;
	int		i;

	splitted_data = ft_split(s, ',');
	if (!splitted_data)
		return (false);
	if (ft_strarr_len(splitted_data) != 3)
	{
		free_splited_data(splitted_data);
		return (false);
	}
    i = 0;
    while (i < 3)
    {
        if (is_double(splitted_data[i]) == false)
        {
            free_splited_data(splitted_data);
            return (false);
        }
        point->v[i] = ft_strtod(splitted_data[i]);
        i++;
    }
    free_splited_data(splitted_data);
	return (true);
}
