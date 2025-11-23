/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:14:18 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/23 19:10:15 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void notify_err_line_content(char *s)
{
	ft_puterr("at line \"");
	ft_puterr(s);
	ft_puterr("\": parse error\n");
}
