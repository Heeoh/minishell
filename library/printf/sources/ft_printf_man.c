/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_man.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:52:30 by heson             #+#    #+#             */
/*   Updated: 2023/02/15 15:22:34 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"
#include "../headers/ft_printf_type_utils.h"
#include "../headers/ft_printf_format_utils.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

char	g_types[TYPE_N] = {'c', 's', 'p', 'd', 'i', 'u', 'x', 'X', '%'};
int		(*g_to_string_by_type[TYPE_N])(t_data *, t_format, va_list)
	= {get_data_c, get_data_s, get_data_p,
	get_data_di, get_data_di, get_data_u,
	get_data_x, get_data_x};

const char	*check_format(const char *p, t_format *format)
{
	init_format(format);
	if (p && *p)
	{
		if ('1' <= *p && *p <= '9')
		{
			format->field_width = *p++ - '0';
			while ('0' <= *p && *p <= '9')
				format->field_width = (format->field_width * 10) + (*p++ - '0');
		}
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

int	get_printed_data(t_data *printed, t_format format, t_data argu_data)
{
	char	*p;
	char	*data_p;
	int		cnt;

	if (format.field_width > (int)argu_data.len)
		printed->len = format.field_width;
	else
		printed->len = argu_data.len;
	printed->str = (char *)malloc(printed->len + 1);
	if (!printed->str)
		return (ERROR_I);
	p = printed->str;
	cnt = printed->len;
	while (cnt-- > (int)argu_data.len)
		*p++ = ' ';
	data_p = argu_data.str;
	while (cnt-- >= 0)
		*p++ = *data_p++;
	*p = '\0';
	return (printed->len);
}

int	print_by_format(t_format format, va_list ap)
{
	t_data			argu_data;
	t_data			printed_data;
	unsigned int	cnt;
	char			*p;

	if (get_data(&argu_data, format, ap) == ERROR_I)
		return (ERROR_I);
	if (get_printed_data(&printed_data, format, argu_data) == ERROR_I)
		return (ERROR_I);
	free(argu_data.str);
	p = printed_data.str;
	cnt = 0;
	while (cnt++ < printed_data.len)
		write(1, p++, 1);
	free(printed_data.str);
	return (printed_data.len);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			printed_len;
	t_format	format;

	printed_len = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str = check_format(++str, &format);
			if (!str)
				return (ERROR_I);
			else if (format.type != TYPE_INIT)
			{
				printed_len += print_by_format(format, ap);
				str++;
				continue ;
			}
		}
		write(1, str++, 1);
		printed_len++;
	}
	return (printed_len);
}

// #include <limits.h>
// #include <stdio.h>

// int main() {

// 	int mine = ft_printf("hello, %d\n");
// 	// int ans = printf("%%\n");
// 	// printf("a: %d, m: %d\n", mine, ans);

// 	// while(1);
// }
