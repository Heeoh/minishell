/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_man.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:45:28 by heson             #+#    #+#             */
/*   Updated: 2022/07/27 16:19:09 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_num_len(int num)
{
	int	cnt;

	cnt = 0;
	if (num <= 0)
		cnt++;
	while (num != 0)
	{
		num /= 10;
		cnt++;
	}
	return (cnt);
}

unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	unsigned int	res_len;
	char			*res;
	char			*p;

	res_len = get_num_len(n);
	res = (char *)malloc(res_len + 1);
	if (!res)
		return (NULL);
	p = res + res_len;
	*p-- = '\0';
	if (n == 0)
		*p = '0';
	else if (n < 0)
		*res = '-';
	while (n != 0)
	{
		*p-- = ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (res);
}
