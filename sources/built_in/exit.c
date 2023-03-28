/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:46:05 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/28 14:16:21 by heson            ###   ########.fr       */
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
	if (cmd->ac == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else
	{
		if (cmd->av[1] && is_num(cmd->av[1]))
			exit_argm(cmd->av[1]);
		else if (cmd->ac > 2)
		{
			printf("miniHell: too many arguments\n");
			return (1);
		}
	}
	printf("exit\n");
	exit(ft_atoi(cmd->av[1]));
}
