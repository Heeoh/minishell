/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:25:05 by heson             #+#    #+#             */
/*   Updated: 2023/02/15 15:22:57 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../headers/ft_printf_utils.h"

size_t	get_abs_num_len(unsigned long long num)
{
	size_t	cnt;

	cnt = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		cnt++;
	}
	return (cnt);
}

char	*convert_abs_num_2_array(unsigned long long n, size_t len)
{
	char	*res;
	char	*p;

	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	p = res + len;
	*p-- = '\0';
	if (n == 0)
		*p = '0';
	while (n != 0)
	{
		*p-- = n % 10 + '0';
		n /= 10;
	}
	return (res);
}

char	*my_itoa(long n)
{
	size_t	res_len;
	char	*res;
	int		sign;

	sign = 1;
	res_len = 0;
	if (n < 0)
	{
		n = -n;
		sign = -1;
		res_len++;
	}
	res_len += get_abs_num_len(n);
	res = convert_abs_num_2_array(n, res_len);
	if (sign < 0)
		res[0] = '-';
	return (res);
}

char	*ft_uitoa(unsigned long n)
{
	size_t	res_len;
	char	*res;

	res_len = get_abs_num_len(n);
	res = convert_abs_num_2_array(n, res_len);
	return (res);
}

char	*ft_ulltoa(unsigned long long n)
{
	size_t	res_len;
	char	*res;

	res_len = get_abs_num_len(n);
	res = convert_abs_num_2_array(n, res_len);
	return (res);
}
