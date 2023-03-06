/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag2_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:06:05 by heson             #+#    #+#             */
/*   Updated: 2023/02/15 15:22:14 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"
#include "../headers/ft_printf_utils.h"

#include <stdlib.h>

char	*apply_hash_flag(char *str, t_format foramt, size_t *len)
{
	char	*res;

	res = NULL;
	if (!(foramt.type == UPPER_X || foramt.type == LOWER_X
			|| foramt.type == POINTER))
		return (ERROR_P);
	*len += 2;
	res = ft_strjoin("0x", str, *len);
	free(str);
	return (res);
}

char	*apply_plus_flag(char *str, t_format foramt, size_t *len)
{
	char	*res;

	res = str;
	if (!(foramt.type == DECIMAL || foramt.type == INT))
		return (ERROR_P);
	if (*str != '-')
	{
		*len += 1;
		res = ft_strjoin("+", str, *len);
		free(str);
	}
	return (res);
}

char	*apply_space_flag(char *str, t_format foramt, size_t *len)
{
	char	*res;

	res = str;
	if (!(foramt.type == DECIMAL || foramt.type == INT))
		return (ERROR_P);
	if (*str != '-')
	{
		*len += 1;
		res = ft_strjoin(" ", str, *len);
		free(str);
	}
	return (res);
}
