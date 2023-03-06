/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_man.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:05:33 by heson             #+#    #+#             */
/*   Updated: 2022/07/27 16:21:01 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, const char *set)
{
	while (set && *set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	const char	*p;
	const char	*end_p;
	char		*res_p;

	if (!s1)
		return (NULL);
	p = s1 + ft_strlen(s1) - 1;
	while (p >= s1 && is_set(*p, set))
		p--;
	end_p = p + 1;
	p = s1;
	while (p < end_p && is_set(*p, set))
		p++;
	res = (char *)malloc(end_p - p + 1);
	if (!res)
		return (NULL);
	res_p = res;
	while (p < end_p)
		*res_p++ = *p++;
	*res_p = '\0';
	return (res);
}
