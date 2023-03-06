/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:39:33 by heson             #+#    #+#             */
/*   Updated: 2023/02/15 15:22:23 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"
#include "../headers/ft_printf_flag_utils.h"
#include "../headers/ft_printf_type_utils.h"
#include "../headers/ft_printf_format_utils.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

char	g_types[TYPE_N] = {'c', 's', 'p', 'd', 'i', 'u', 'x', 'X', '%'};
char	g_flags[FLAG_N] = {'-', '0', '.', '#', '+', ' '};
int		(*g_to_string_by_type[TYPE_N])(t_data *, t_format, va_list)
	= {get_data_c, get_data_s, get_data_p,
	get_data_di, get_data_di, get_data_u,
	get_data_x, get_data_x};

const char	*check_format(const char *p, t_format *format)
{
	int	flag_i;

	init_format(format);
	while (p && *p)
	{
		flag_i = checker(p, g_flags, FLAG_N);
		if (flag_i != FLAG_N)
		{
			format->flags[flag_i] = TRUE;
			if (flag_i == PRECISION)
			{
				p = atoi_iter(++p, &format->flags[PRECISION]);
				continue ;
			}
			p++;
			continue ;
		}
		if (!format->field_width)
			p = atoi_iter(p, &format->field_width);
		format->type = checker(p, g_types, TYPE_N);
		if (format->type != TYPE_N)
			return (check_right_format(format, p));
	}
	return (ERROR_P);
}

int	get_data(t_data *data, t_format format, va_list ap)
{
	int	ret;

	data->len = 0;
	if (format.type == PERCENT)
		ret = get_data_per(data);
	else
		ret = g_to_string_by_type[format.type](data, format, ap);
	return (ret);
}

int	get_printed_data(t_data *printed, t_format format_info, t_data argu_data)
{
	char	*p;
	int		cnt;

	printed->len = argu_data.len;
	if (format_info.field_width > (int)argu_data.len)
		printed->len = format_info.field_width;
	printed->str = (char *)malloc(printed->len + 1);
	if (!printed->str)
		return (ERROR_I);
	if (format_info.flags[MINUS])
		p = apply_minus_flag(printed->str, &(printed->len));
	else if (format_info.flags[ZERO])
		p = apply_zero_flag(printed, format_info, &argu_data);
	else
	{
		p = printed->str;
		cnt = printed->len;
		while (cnt-- > (int)argu_data.len)
			*p++ = ' ';
	}	
	cnt = 0;
	while (cnt < (int)argu_data.len)
		*p++ = argu_data.str[cnt++];
	*(printed->str + printed->len) = '\0';
	return (printed->len);
}

int	print_by_format(t_format format_info, va_list ap)
{
	t_data			argu_data;
	t_data			printed_data;
	unsigned int	cnt;
	char			*p;

	if (get_data(&argu_data, format_info, ap) == ERROR_I)
		return (ERROR_I);
	if (get_printed_data(&printed_data, format_info, argu_data) == ERROR_I)
		return (ERROR_I);
	free(argu_data.str);
	p = printed_data.str;
	cnt = 0;
	while (cnt++ < printed_data.len)
		write(1, p++, 1);
	free(printed_data.str);
	return (printed_data.len);
}

int	ft_printf(const char *str_p, ...)
{
	va_list		ap;
	int			printed_len;
	t_format	format;

	printed_len = 0;
	va_start(ap, str_p);
	while (*str_p)
	{
		if (*str_p == '%')
		{
			str_p = check_format(++str_p, &format);
			if (!str_p)
				return (ERROR_I);
			else if (format.type != TYPE_INIT)
			{
				printed_len += print_by_format(format, ap);
				str_p++;
				continue ;
			}
		}
		write(1, str_p++, 1);
		printed_len++;
	}
	return (printed_len);
}

// #include <limits.h>
// #include <stdio.h>

// int main() {
// 	int mine = ft_printf("%10.5%\n");
// 	int ans = printf("%10.5%\n");
// 	printf("%d, %d\n", mine, ans);

// 	// while(1);
// }
