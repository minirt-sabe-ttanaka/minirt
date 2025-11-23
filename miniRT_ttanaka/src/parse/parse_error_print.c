/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:14:18 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/23 14:14:29 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void notify_err_line_num(size_t line_num)
{
	ft_puterr("at line ");
	ft_putnbr_fd(line_num, STDERR_FILENO);
	ft_puterr(": ");
}
