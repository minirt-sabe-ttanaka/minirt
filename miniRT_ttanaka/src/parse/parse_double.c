#include "parse.h"

static bool	is_double(char *s);
bool		parse_double(char *s, double *val);

bool	is_double(char *s)
{
	bool	has_digit;

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

bool	parse_double(char *s, double *val)
{
	if (is_double(s) == false)
		return (false);
	*val = ft_strtod(s);
	return (true);
}
