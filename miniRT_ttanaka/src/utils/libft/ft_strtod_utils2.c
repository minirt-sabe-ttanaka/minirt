#include "utils/libft.h"

void	init_power_table(void);
void	calc_product(t_calc_ctx *ctx, uint64_t mant, int exp10);
void	apply_rounding(t_calc_ctx *ctx, uint64_t *m53);
double	pack_double(t_calc_ctx *ctx);
void	parse_mantissa(const char **s, uint64_t *mant, int *exp);

void	init_power_table(void)
{
	t_u128	base_val;

	base_val = ((t_u128)1 << 127);
	store_entry(TABLE_OFFSET, base_val, -127);
	fill_positive_powers();
	fill_negative_powers();
}

void    calc_product(t_calc_ctx *ctx, uint64_t mant, int exp10)
{
    t_power_table   *tab;
    t_power_table   entry;
    t_u128          sig_128;
    t_u128          prod;

    tab = get_table();
    entry = tab[exp10 + TABLE_OFFSET];
    sig_128 = ((t_u128)entry.sig_hi << 64) | entry.sig_lo;
    prod = (t_u128)mant * (sig_128 >> 64);
    ctx->upper = (uint64_t)(prod >> 64);
    ctx->lower = (uint64_t)prod;
    ctx->bin_exp = entry.biased_exp + 128;
    while ((ctx->upper & 0x8000000000000000ULL) == 0)
    {
        prod <<= 1;
        ctx->upper = (uint64_t)(prod >> 64);
        ctx->lower = (uint64_t)prod;
        ctx->bin_exp -= 1;
    }
}

void	apply_rounding(t_calc_ctx *ctx, uint64_t *m53)
{
	uint64_t	round_bits;
	bool		sticky;
	bool		round_bit;
	bool		lsb;

	round_bits = ctx->upper & 0x7FF;
	sticky = (ctx->lower != 0);
	if ((round_bits & 0x3FF) != 0)
		sticky = true;
	round_bit = (round_bits & 0x400) != 0;
	lsb = (*m53 & 1) != 0;
	if (round_bit)
	{
		if (sticky || lsb)
		{
			(*m53)++;
			if ((*m53 & 0x0020000000000000ULL) != 0)
			{
				*m53 >>= 1;
				ctx->bin_exp++;
			}
		}
	}
}

double	pack_double(t_calc_ctx *ctx)
{
	t_ieee64	res;
	uint64_t	m53;
	int64_t		exp;

	m53 = ctx->upper >> 11;
	apply_rounding(ctx, &m53);
	exp = ctx->bin_exp + 1023 + 63;
	if (exp >= 2047)
	{
		res.u = 0x7FF0000000000000ULL | ((uint64_t)ctx->neg << 63);
		return (res.d);
	}
	if (exp <= 0)
	{
		res.u = (uint64_t)ctx->neg << 63;
		return (res.d);
	}
	res.u = ((uint64_t)ctx->neg << 63) | ((uint64_t)exp << 52);
	res.u |= (m53 & 0xFFFFFFFFFFFFFULL);
	return (res.d);
}

void	parse_mantissa(const char **s, uint64_t *mant, int *exp)
{
	bool	dot;

	*mant = 0;
	*exp = 0;
	dot = false;
	while (**s)
	{
		if (**s >= '0' && **s <= '9')
		{
			if (*mant < (UINT64_MAX / 10))
			{
				*mant = *mant * 10 + (**s - '0');
				if (dot)
					(*exp)--;
			}
			else if (!dot)
				(*exp)++;
		}
		else if (**s == '.' && !dot)
			dot = true;
		else
			break ;
		(*s)++;
	}
}
