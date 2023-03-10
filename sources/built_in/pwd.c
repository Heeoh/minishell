/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:58:15 by heson             #+#    #+#             */
/*   Updated: 2023/03/13 21:31:20 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../library/libft/libft.h"
// #include <stdio.h> //printf

void	ft_pwd(void)
{
	char	*ret;
	int		buffer_size;

	buffer_size = 256;
	ret = getcwd(0, buffer_size);
	while (!ret)
	{
		buffer_size *= 2;
		ret = getcwd(0, buffer_size);
	}
	ft_putendl_fd(ret, STDOUT_FILENO);
}

// int main() {
//     ft_pwd();
// }