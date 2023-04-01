/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:46:05 by jkim3             #+#    #+#             */
/*   Updated: 2023/04/01 17:43:26 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

int	is_range(int minus, char *str)
{
	if (minus)
	{
		if (ft_strcmp("9223372036854775808", str) < 0)
			return (0);
	}
	else
	{
		if (ft_strcmp("9223372036854775807", str) < 0)
			return (0);
	}
	return (1);
}

int	is_num(char *str)
{
	int	i;
	int	minus;

	i = 0;
	minus = 0;
	if (*str == '-')
		minus++;
	if (*str == '-' || *str == '+')
		str++;
	if (ft_strlen(str) > 19)
		return (0);
	else if (ft_strlen(str) == 19 && !is_range(minus, str))
		return (0);
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
