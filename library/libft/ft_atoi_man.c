/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_man.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:15:08 by heson             #+#    #+#             */
/*   Updated: 2023/01/19 01:04:48 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	char				*p;
	int					sign;
	unsigned long long	absolute_num;

	p = (char *)str;
	sign = 1;
	while (*p && (*p == ' ' || (9 <= *p && *p <= 13)))
		p++;
	if (*p == '-' || *p == '+')
	{
		if (*p == '-')
			sign = -1;
		p++;
	}
	absolute_num = 0;
	while (*p && '0' <= *p && *p <= '9')
	{
		absolute_num = absolute_num * 10 + (*p - '0');
		if (sign == 1 && absolute_num >= LLONG_MAX)
			return (-1);
		if (sign == -1 && absolute_num > LLONG_MAX)
			return (0);
		p++;
	}
	return (absolute_num * sign);
}
