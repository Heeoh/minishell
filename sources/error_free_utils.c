/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:50:52 by jkim3             #+#    #+#             */
/*   Updated: 2023/04/01 18:53:48 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "built_in.h"

void	ft_free_str(char **arg)
{
	if (arg && *arg)
		free(*arg);
	*arg = NULL;
}

int	perror_n_return(char *err_pos, char *err_msg,
					int is_custom, int exit_status)
{
	extern int	g_exit_status;

	g_exit_status = exit_status;
	ft_putstr_fd("minishell: ", 2);
	if (err_pos)
	{
		ft_putstr_fd(err_pos, 2);
		write(2, ": ", 2);
	}
	if (!is_custom && err_msg && *err_msg)
	{
		ft_putstr_fd(err_msg, 2);
		write(2, ": ", 2);
	}
	if (is_custom)
		ft_putendl_fd(err_msg, 2);
	else
		perror("");
	return (-1);
}

void	perror_n_exit(char *err_msg, int is_custom, int exit_status)
{
	perror_n_return(0, err_msg, is_custom, exit_status);
	exit(g_exit_status);
}
