/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:38:22 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/22 02:10:34 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBFT_H__
# define __LIBFT_H__

# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

void						*ft_calloc(size_t count, size_t size);
void						ft_putchar_fd(char c, int fd);
void						ft_putstr_fd(char *s, int fd);
void						ft_putendl_fd(char *s, int fd);
char						*ft_strrchr(const char *s, int c);
int							ft_strcmp(char *s1, char *s2);
char						**ft_split(char const *s, char c);
void						free_splited_data(char **data);
size_t						ft_strarr_len(char **strarr);
int							ft_isdigit(int c);
int							ft_atoi(const char *str);
size_t						ft_strlen(const char *s);
int							ft_isspace(char c);
void						*ft_memset(void *s, int c, size_t n);

/* ft_strtod.c */
typedef unsigned __int128	t_u128;

# define TABLE_OFFSET 325
# define TABLE_SIZE 634

typedef union u_ieee64
{
	double					d;
	uint64_t				u;
}							t_ieee64;

typedef struct s_power_table
{
	uint64_t				sig_hi;
	uint64_t				sig_lo;
	int						biased_exp;
}							t_power_table;

typedef struct s_calc_ctx
{
	uint64_t				upper;
	uint64_t				lower;
	int						bin_exp;
	bool					neg;
}							t_calc_ctx;

t_power_table				*get_table(void);
void						normalize_val(t_u128 *val, int *exp);
void						store_entry(int idx, t_u128 val, int exp);
void						fill_positive_powers(void);
void						fill_negative_powers(void);
void						init_power_table(void);
void						calc_product(t_calc_ctx *ctx, uint64_t mant,
								int exp10);
void						apply_rounding(t_calc_ctx *ctx, uint64_t *m53);
double						pack_double(t_calc_ctx *ctx);
void						parse_mantissa(const char **s, uint64_t *mant,
								int *exp);
void						parse_scientific(const char **s, int *exp);
double						ft_strtod(const char *str);

#endif
