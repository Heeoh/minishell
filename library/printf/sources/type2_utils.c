/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type2_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:43:28 by heson             #+#    #+#             */
/*   Updated: 2023/02/15 15:22:44 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf_type_utils.h"
#include "../headers/ft_printf_flag_utils.h"
#include "../headers/ft_printf_utils.h"

#include <stdlib.h> // free

int	get_data_c(t_data *data, t_format format, va_list ap)
{
	char	tmp[2];

	if (format.type != CHAR)
		return (ERROR_I);
	tmp[0] = (char)va_arg(ap, int);
	tmp[1] = '\0';
	data->len = 1;
	data->str = ft_strndup(tmp, &(data->len));
	if (!data->str)
		return (ERROR_I);
	return (data->len);
}

int	get_data_s(t_data *data, t_format format, va_list ap)
{
	char	*tmp;

	if (format.type != STR)
		return (ERROR_I);
	tmp = va_arg(ap, char *);
	if (!tmp)
		data->str = ft_strndup("(null)", &(data->len));
	else
		data->str = ft_strndup(tmp, &(data->len));
	if (format.flags[PRECISION] != -1)
			data->str = apply_precision_flag(data->str, format, data);
	if (!data->str)
		return (ERROR_I);
	return (data->len);
}

int	get_data_p(t_data *data, t_format format, va_list ap)
{
	unsigned long long	tmp_n;
	char				*tmp_str[2];

	if (format.type != POINTER)
		return (ERROR_I);
	tmp_n = va_arg(ap, unsigned long long);
	tmp_str[0] = ft_ulltoa(tmp_n);
	tmp_str[1] = ft_convert_base(tmp_str[0], "0123456789", "0123456789abcdef");
	data->str = ft_strndup(tmp_str[1], &(data->len));
	data->str = apply_hash_flag(data->str, format, &(data->len));
	free(tmp_str[0]);
	free(tmp_str[1]);
	if (!data->str)
		return (ERROR_I);
	return (data->len);
}

int	get_data_per(t_data *data)
{
	data->str = ft_strndup("%", &(data->len));
	return (data->len);
}
