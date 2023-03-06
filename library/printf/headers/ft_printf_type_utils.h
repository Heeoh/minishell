/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:01:25 by heson             #+#    #+#             */
/*   Updated: 2022/12/14 16:48:56 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_TYPE_UTILS_H
# define FT_PRINTF_TYPE_UTILS_H

# include "ft_printf.h"
# include <stdarg.h>

int	get_data_c(t_data *data, t_format format, va_list ap);
int	get_data_s(t_data *data, t_format format, va_list ap);
int	get_data_di(t_data *data, t_format format, va_list ap);
int	get_data_u(t_data *data, t_format format, va_list ap);
int	get_data_x(t_data *data, t_format format, va_list ap);
int	get_data_p(t_data *data, t_format format, va_list ap);
int	get_data_per(t_data *data);

#endif