/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:22:32 by heson             #+#    #+#             */
/*   Updated: 2023/02/15 15:23:04 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../headers/ft_printf_utils.h"

char	*ft_strjoin(char const *s1, char const *s2, size_t len)
{
	char		*res;
	const char	*p;
	char		*res_p;

	res = (char *)malloc(len + 1);
	if (!res)
		return (ERROR_P);
	res_p = res;
	p = s1;
	while (s1 && *p)
		*res_p++ = *p++;
	p = s2;
	while (s2 && *p)
		*res_p++ = *p++;
	*res_p = '\0';
	return (res);
}
