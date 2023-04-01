/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:27:05 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:37:03 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(int cmd_i, int cmd_cnt, int pipes[][2], int is_heredoc)
{
	if (cmd_i != 0 && !is_heredoc)
	{
		if (dup2(pipes[(cmd_i + 1) % PIPE_N][R_FD], STDIN_FILENO) < 0)
			perror_n_exit(0, 0, EXIT_FAILURE);
	}
	if (cmd_i != cmd_cnt - 1)
	{
		if (dup2(pipes[cmd_i % PIPE_N][W_FD], STDOUT_FILENO) < 0)
			perror_n_exit(0, 0, EXIT_FAILURE);
	}
	close(pipes[cmd_i % PIPE_N][R_FD]);
	close(pipes[cmd_i % PIPE_N][W_FD]);
	return (0);
}

void	parent_process(int cmd_i, int pipes[][2])
{
	close(pipes[cmd_i % PIPE_N][W_FD]);
	if (cmd_i != 0)
		close(pipes[(cmd_i + 1) % PIPE_N][R_FD]);
}

int	wait_processes(int child_cnt, pid_t last_pid, pid_t wait_pid)
{
	int	status;
	int	signal_exit;

	signal_exit = 0;
	while (child_cnt--)
	{
		wait_pid = waitpid(-1, &status, 0);
		if (wait_pid < 0)
			perror_n_exit("wait child process", 0, status);
		if (!signal_exit && WIFSIGNALED(status) && WTERMSIG(status) == 2)
		{
			signal_exit = 1;
			ft_putstr_fd("\n", 2);
		}
		if (!signal_exit && WIFSIGNALED(status) && WTERMSIG(status) == 3)
		{
			signal_exit = 1;
			ft_putstr_fd("Quit: 3\n", 2);
		}
		if (wait_pid == last_pid)
			set_exit_status(status);
	}
	return (0);
}
