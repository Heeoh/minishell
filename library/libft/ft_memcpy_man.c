/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_man.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:48:28 by heson             #+#    #+#             */
/*   Updated: 2022/07/27 16:19:35 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)dst;
	if (!dst && !src)
		return (NULL);
	while (n--)
	{
		*p++ = *(unsigned char *)src;
		src++;
	}
	return (dst);
}
