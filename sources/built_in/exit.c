/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:46:05 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/31 18:41:55 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_argm(char *argm)
{
	printf("exit\n");
	per_n_ret("exit", argm, "numeric argument required", 1);
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
		if (cmd->av[1] && !is_num(cmd->av[1]))
			exit_argm(cmd->av[1]);
		else if (cmd->ac > 2)
		{
			printf("exit\n");
			return (perror_n_return("exit", "too many arguments", 1, 1));
		}
	}
	printf("exit\n");
	g_exit_status = ft_atoi(cmd->av[1]);
	g_exit_status %= 256;
	if (g_exit_status < 0)
		g_exit_status += 256;
	exit(g_exit_status);
}
