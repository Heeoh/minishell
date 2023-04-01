/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:11:11 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:39:19 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static	int	check_option_n(int ac, char **av, int *idx)
{
	char	*p;
	int		option_n;

	option_n = 0;
	*idx = 1;
	while (*idx < ac)
	{
		p = av[*idx];
		if (p && *p == '-')
		{
			while (p++ && *p)
			{
				if (*p != 'n')
					return (option_n);
			}
			option_n = 1;
		}
		else
			return (option_n);
		(*idx)++;
	}
	return (option_n);
}

int	ft_echo(t_cmd *cmd)
{
	int		option_n;
	int		val_idx;

	option_n = check_option_n(cmd->ac, cmd->av, &val_idx);
	while (val_idx < cmd->ac)
	{
		ft_putstr_fd(cmd->av[val_idx], STDOUT_FILENO);
		val_idx++;
		if (val_idx < cmd->ac)
			write(STDOUT_FILENO, " ", 1);
	}
	if (!option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
