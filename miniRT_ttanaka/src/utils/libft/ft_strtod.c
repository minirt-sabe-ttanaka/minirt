#include "utils/libft.h"

void	parse_scientific(const char **s, int *exp);
double	ft_strtod(const char *str);

void	parse_scientific(const char **s, int *exp)
{
	int	e_val;
	int	e_sign;

	if (**s != 'e' && **s != 'E')
		return ;
	(*s)++;
	e_sign = 1;
	e_val = 0;
	if (**s == '-')
	{
		e_sign = -1;
		(*s)++;
	}
	else if (**s == '+')
		(*s)++;
	while (**s >= '0' && **s <= '9')
	{
		if (e_val < 10000)
			e_val = e_val * 10 + (**s - '0');
		(*s)++;
	}
	*exp += (e_val * e_sign);
}

double	ft_strtod(const char *str)
{
	uint64_t	mant;
	int			exp;
	t_calc_ctx	ctx;
	static bool is_initialized = false;

	if (!is_initialized)
    {
        init_power_table();
        is_initialized = true;
    }
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	ctx.neg = false;
	if (*str == '-')
	{
		ctx.neg = true;
		str++;
	}
	else if (*str == '+')
		str++;
	parse_mantissa(&str, &mant, &exp);
	parse_scientific(&str, &exp);
	if (mant == 0)
	{
		if (ctx.neg)
			return (-0.0);
		return (0.0);
	}
	calc_product(&ctx, mant, exp);
	return (pack_double(&ctx));
}

// void	print_res(const char *s)
// {
// 	double		d;
// 	t_ieee64	u;

// 	d = ft_strtod(s);
// 	u.d = d;
// 	printf("In: %-10s | Out: %.17g\n", s, d);
// 	printf("Hex: 0x%016llx\n\n", u.u);
// }

// int	main(void)
// {
// 	init_power_table();
// 	print_res("5.75");
// 	print_res("0.1");
// 	print_res("-123.456");
// 	print_res("SHADOW_BIAS00");
// 	print_res("1e300");
// 	return (0);
// }
