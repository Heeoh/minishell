/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type1_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:43:28 by heson             #+#    #+#             */
/*   Updated: 2023/02/15 15:22:40 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf_type_utils.h"
#include "../headers/ft_printf_flag_utils.h"
#include "../headers/ft_printf_utils.h"

#include <stdlib.h> // free

int	get_data_di(t_data *data, t_format format, va_list ap)
{
	char	*tmp;

	if (!(format.type == DECIMAL || format.type == INT))
		return (ERROR_I);
	tmp = my_itoa(va_arg(ap, int));
	data->str = ft_strndup(tmp, &(data->len));
	if (format.flags[PRECISION] != -1)
		data->str = apply_precision_flag(data->str, format, data);
	if (format.flags[PLUS])
		data->str = apply_plus_flag(data->str, format, &(data->len));
	else if (format.flags[SPACE])
		data->str = apply_space_flag(data->str, format, &(data->len));
	free(tmp);
	if (!data->str)
		return (ERROR_I);
	return (data->len);
}

int	get_data_u(t_data *data, t_format format, va_list ap)
{
	char	*tmp;

	if (format.type != U_INT)
		return (ERROR_I);
	tmp = ft_uitoa(va_arg(ap, unsigned int));
	data->str = ft_strndup(tmp, &(data->len));
	if (format.flags[PRECISION] != -1)
		data->str = apply_precision_flag(data->str, format, data);
	free(tmp);
	if (!data->str)
		return (ERROR_I);
	return (data->len);
}

int	get_data_x(t_data *data, t_format format, va_list ap)
{
	unsigned int	tmp_n;
	char			*tmp[2];

	if (!(format.type == LOWER_X || format.type == UPPER_X))
		return (ERROR_I);
	tmp_n = va_arg(ap, unsigned int);
	tmp[0] = my_itoa(tmp_n);
	tmp[1] = ft_convert_base(tmp[0], "0123456789", "0123456789abcdef");
	data->str = ft_strndup(tmp[1], &(data->len));
	if (format.flags[PRECISION] != -1)
		data->str = apply_precision_flag(data->str, format, data);
	if (format.flags[HASH] && tmp_n != 0)
		data->str = apply_hash_flag(data->str, format, &(data->len));
	free(tmp[0]);
	free(tmp[1]);
	if (!data->str)
		return (ERROR_I);
	if (format.type == UPPER_X)
		ft_str_toupper(data->str);
	return (data->len);
}
