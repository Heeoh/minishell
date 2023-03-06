/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_utils.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:43:53 by heson             #+#    #+#             */
/*   Updated: 2022/12/14 16:48:23 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FORMAT_UTILS_H
# define FT_PRINTF_FORMAT_UTILS_H

# include "ft_printf.h"

void		init_format(t_format *format);
const char	*atoi_iter(const char *p, int *ret);
int			checker(const char *p, char *target, int n);
const char	*check_right_format(t_format *format, const char *right_sign);

#endif