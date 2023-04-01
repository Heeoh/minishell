/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:06:24 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:34:50 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2d_arr(char **arr)
{
	char	**p;

	p = arr;
	while (p && *p)
	{
		free(*p);
		p++;
	}
	free(arr);
}

void	set_exit_status(int status)
{
	g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_exit_status = WTERMSIG(status);
		if (WTERMSIG(status) == 2)
			g_exit_status = 130;
		else if (WTERMSIG(status) == 3)
			g_exit_status = 131;
	}
}

void	set_child_exe(int fd_std[], int heredoc_fd)
{
	close(fd_std[R_FD]);
	close(fd_std[W_FD]);
	if (heredoc_fd >= 0)
		close(heredoc_fd);
	set_ctrl(1, SIG_DFL, SIG_DFL);
}

void	close_fds(int fds[][2])
{
	if (fds[0][R_FD] > 0)
		close(fds[0][R_FD]);
	if (fds[0][W_FD] > 0)
		close(fds[0][W_FD]);
	if (fds[1][R_FD] > 0)
		close(fds[1][R_FD]);
	if (fds[1][W_FD] > 0)
		close(fds[1][W_FD]);
	if (fds[STD][R_FD] > 0)
		close(fds[STD][R_FD]);
	if (fds[STD][W_FD] > 0)
		close(fds[STD][W_FD]);
}
