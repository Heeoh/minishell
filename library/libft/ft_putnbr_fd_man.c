/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_man.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:21:18 by heson             #+#    #+#             */
/*   Updated: 2022/07/27 16:19:59 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			res[10];
	unsigned int	i;
	int				write_n;

	if (fd < 0)
		return ;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
		write(fd, "-", 1);
	i = 0;
	while (n != 0)
	{
		write_n = n % 10;
		if (write_n < 0)
			write_n = -write_n;
		res[i++] = write_n + '0';
		n /= 10;
	}
	while (i--)
		write(fd, &res[i], 1);
}
