/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:25:29 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:37:47 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	get_heredoc_input(int fd[], int fd_std[], char *limiter)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	close(fd[R_FD]);
	while (1)
	{
		write(fd_std[W_FD], "> ", 2);
		line = get_next_line(fd_std[R_FD]);
		if (!line)
			break ;
		if (ft_strlen(line) - 1 == ft_strlen(limiter)
			&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[W_FD]);
		free(line);
	}
	close(fd[W_FD]);
	close(fd_std[R_FD]);
	close(fd_std[W_FD]);
	return (0);
}

int	wait_heredoc_input(int fd[], pid_t child_pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(fd[W_FD]);
	if (waitpid(child_pid, &status, 0) < 0)
		perror_n_return("waitpid", 0, 0, EXIT_FAILURE);
	if (WIFEXITED(status))
		return (fd[R_FD]);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			ft_putstr_fd("\n", 2);
			g_exit_status = 1;
		}
	}
	return (ERROR);
}
