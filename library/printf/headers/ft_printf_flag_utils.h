/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:17:15 by heson             #+#    #+#             */
/*   Updated: 2022/12/14 16:47:58 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FLAG_UTILS_H
# define FT_PRINTF_FLAG_UTILS_H

# include "ft_printf.h"

char	*apply_minus_flag(char *str, size_t *len);
char	*apply_zero_flag(t_data	*printed, t_format format, t_data *data);
char	*apply_precision_flag(char *str, t_format format, t_data *data);
char	*apply_hash_flag(char *str, t_format format, size_t	*len);
char	*apply_plus_flag(char *str, t_format format, size_t *len);
char	*apply_space_flag(char *str, t_format format, size_t *len);

#endif