/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:46:05 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/24 20:03:13 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int is_num(char *str)
{
	int	i;

	i = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	exit_argm(char *argm)
{
	printf("exit\n");
	printf("miniHell: exit: %s:  numeric argument required\n", argm);
	exit(255);
}

int	ft_exit(t_cmd *cmd)
{
	if (!cmd->av[2])
	{
		printf("exit\n");
		exit(0);
	}
	else
	{
		if (is_num(cmd->av[2]))
			exit_argm(cmd->av[2]);
		else if (cmd->av[3])
		{
			printf("miniHell: too many arguments\n");
			return (1);
		}
	}
	printf("exit\n");
	exit(ft_atoi(cmd->av[2]));
}
