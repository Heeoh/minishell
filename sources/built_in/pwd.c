/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:58:15 by heson             #+#    #+#             */
/*   Updated: 2023/03/31 17:52:13 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../library/libft/libft.h"
#include "../../headers/minishell.h"
// #include <stdio.h> //printf

int	ft_pwd(t_cmd *cmd)
{
	char	*ret;

	if (cmd->ac == 1)
	{
		ret = getcwd(NULL, 0);
		if (ret)
			ft_putendl_fd(ret, STDOUT_FILENO);
		// else //perror
		// 	return (EXIT_FAILURE);
	}
	else
	{
		perror_n_return("pwd", "too many arguments", 1, 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// int main() {
//     ft_pwd();
// }