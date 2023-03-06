/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:34:22 by heson             #+#    #+#             */
/*   Updated: 2023/02/15 15:22:50 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../headers/ft_printf_utils.h"

char	*itoa_base(unsigned long long num, char *base, int base_n);

char	check_dup(char *val, unsigned int cur_i, char c)
{
	unsigned int	i;

	i = 0;
	while (i < cur_i)
	{
		if (val[i] == c)
			return (0);
		i++;
	}
	return (1);
}

unsigned int	is_right_base(char *base)
{
	unsigned int	i;

	i = 0;
	while (base[i])
	{
		if (!(base[i] == '+' || base[i] == '-')
			&& !(base[i] == ' ' || (9 <= base[i] && base[i] <= 13))
			&& check_dup(base, i, base[i]))
			i++;
		else
			return (0);
	}
	return (i);
}

int	find_base_idx(char c, char *base_val, int base_n)
{
	int	i;

	i = 0;
	while (i < base_n)
	{
		if (base_val[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned long long	ft_atoi_base(char *str, char *base, int base_n)
{
	int					base_idx;
	unsigned long long	abs_res;

	abs_res = 0;
	while (*str)
	{
		base_idx = find_base_idx(*str++, base, base_n);
		if (base_idx == -1)
			break ;
		abs_res = abs_res * base_n + base_idx;
	}
	return (abs_res);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int					base_from_n;
	int					base_to_n;
	unsigned long long	num;
	char				*res;

	base_from_n = is_right_base(base_from);
	base_to_n = is_right_base(base_to);
	if (base_from_n <= 1 || base_to_n <= 1)
		return (0);
	num = ft_atoi_base(nbr, base_from, base_from_n);
	res = itoa_base(num, base_to, base_to_n);
	return (res);
}
