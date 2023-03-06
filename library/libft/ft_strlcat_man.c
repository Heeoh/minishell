/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat_man.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:21:17 by heson             #+#    #+#             */
/*   Updated: 2022/07/27 16:20:30 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	unsigned int	dst_len;
	unsigned int	src_len;
	unsigned int	i;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	i = 0;
	while (i < src_len && dst_len + i < dstsize - 1)
	{
		dest[dst_len + i] = src[i];
		i++;
	}
	if (dst_len + i <= dstsize - 1)
		dest[dst_len + i] = '\0';
	return (dst_len + src_len);
}
