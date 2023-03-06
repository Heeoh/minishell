/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_man.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:10:27 by heson             #+#    #+#             */
/*   Updated: 2022/07/27 16:20:25 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*res;
	const char	*p;
	char		*res_p;
	size_t		res_len;

	res_len = 0;
	if (s1)
		res_len += ft_strlen(s1);
	if (s2)
		res_len += ft_strlen(s2);
	res = (char *)malloc(res_len + 1);
	if (!res)
		return (NULL);
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
