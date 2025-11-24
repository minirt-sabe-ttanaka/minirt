/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 14:14:18 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/25 00:22:26 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/parse.h"

void notify_err_line_content(char *s)
{
	ft_puterr("at line \"");
	ft_puterr(s);
	ft_puterr("\": parse error\n");
}
