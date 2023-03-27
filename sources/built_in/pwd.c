/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:58:15 by heson             #+#    #+#             */
/*   Updated: 2023/03/27 22:10:59 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../library/libft/libft.h"
// #include <stdio.h> //printf

int	ft_pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	ft_putendl_fd(ret, STDOUT_FILENO);
	return (0);
}

// int main() {
//     ft_pwd();
// }