/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove_man.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:10:22 by heson             #+#    #+#             */
/*   Updated: 2022/07/27 16:19:38 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p;
	unsigned int	cnt;

	p = (unsigned char *)dst;
	if (!dst && !src)
		return (NULL);
	if (src < dst)
	{
		p += (len - 1);
		cnt = len - 1;
		while (len--)
			*p-- = ((unsigned char *)src)[cnt--];
	}
	else
	{
		while (len--)
			*p++ = *(unsigned char *)src++;
	}
	return (dst);
}
