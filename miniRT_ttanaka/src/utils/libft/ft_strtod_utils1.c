#include "core/utils/libft.h"

t_power_table	*get_table(void);
void			normalize_val(t_u128 *val, int *exp);
void			store_entry(int idx, t_u128 val, int exp);
void			fill_positive_powers(void);
void			fill_negative_powers(void);

t_power_table	*get_table(void)
{
	static t_power_table	table[TABLE_SIZE];

	return (table);
}

/* Shift left to normalize so that the most significant bit (bit 127) is 1.*/
void	normalize_val(t_u128 *val, int *exp)
{
	uint64_t	hi;

	hi = (uint64_t)(*val >> 64);
	if (hi == 0)
	{
		*val <<= 64;
		*exp -= 64;
	}
	while ((*val >> 127) == 0)
	{
		*val <<= 1;
		*exp -= 1;
	}
}

void	store_entry(int idx, t_u128 val, int exp)
{
	t_power_table	*tab;
	t_u128			temp;

	tab = get_table();
	temp = val;
	normalize_val(&temp, &exp);
	tab[idx].sig_hi = (uint64_t)(temp >> 64);
	tab[idx].sig_lo = (uint64_t)temp;
	tab[idx].biased_exp = exp;
}

void	fill_positive_powers(void)
{
	int		i;
	t_u128	val;
	int		exp;

	val = ((t_u128)1 << 127);
	exp = -127;
	i = 1;
	while (i <= 308)
	{
		val >>= 4;
		exp += 4;
		val *= 10;
		store_entry(i + TABLE_OFFSET, val, exp);
		while ((val >> 127) == 0)
		{
			val <<= 1;
			exp -= 1;
		}
		i++;
	}
}

void	fill_negative_powers(void)
{
	int		i;
	t_u128	val;
	int		exp;

	val = ((t_u128)1 << 127);
	exp = -127;
	i = -1;
	while (i >= -325)
	{
		val /= 10;
		while ((val >> 127) == 0)
		{
			val <<= 1;
			exp -= 1;
		}
		store_entry(i + TABLE_OFFSET, val, exp);
		i--;
	}
}

