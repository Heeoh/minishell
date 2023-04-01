/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:21:09 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:39:50 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_redirection(int type, char *val, int *fd)
{
	int	ret;

	if (type == RD_IN)
		ret = do_redirection_in(val, fd, 0);
	if (type == RD_HEREDOC)
		ret = do_redirection_in(val, fd, 1);
	if (type == RD_OUT)
		ret = do_redirection_out(val, fd, 0);
	if (type == RD_APPEND)
		ret = do_redirection_out(val, fd, 1);
	if (*fd > 0 && type != RD_HEREDOC)
		close(*fd);
	if (ret < 0)
		return (ERROR);
	return (0);
}

int	do_redirection_in(char *val, int *fd, char is_heredoc)
{
	int	ret;

	if (!is_heredoc)
		*fd = open(val, O_RDONLY, 0644);
	if (*fd < 0)
		return (perror_n_return(val, 0, 0, EXIT_FAILURE));
	ret = dup2(*fd, STDIN_FILENO);
	if (!is_heredoc)
		close (*fd);
	if (ret < 0)
		return (perror_n_return("dup2", 0, 0, EXIT_FAILURE));
	return (0);
}

int	do_redirection_out(char *filename, int *fd, char is_append)
{
	int	ret;

	if (is_append)
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
		return (perror_n_return(filename, 0, 0, EXIT_FAILURE));
	ret = dup2(*fd, STDOUT_FILENO);
	close(*fd);
	if (ret < 0)
		return (perror_n_return("dup2", 0, 0, EXIT_FAILURE));
	return (0);
}

int	check_n_do_heredoc(t_list *rd_p, int fd_std[], int *fd)
{
	int	is_heredoc;

	is_heredoc = 0;
	*fd = -1;
	while (rd_p)
	{
		if (((t_redirection *)rd_p->content)->type == RD_HEREDOC)
		{
			if (*fd > 0)
				close(*fd);
			*fd = -1;
			is_heredoc = 1;
			if (do_heredoc(((t_redirection *)rd_p->content)->val,
					fd, fd_std) < 0)
				return (ERROR);
		}
		rd_p = rd_p->next;
	}
	return (is_heredoc);
}

int	do_heredoc(char *limiter, int *input_fd, int fd_std[])
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	fd[R_FD] = -1;
	fd[W_FD] = -1;
	line = 0;
	if (pipe(fd) == -1)
		perror_n_exit("pipe", 0, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		perror_n_exit("fork", 0, EXIT_FAILURE);
	else if (!pid)
	{
		if (get_heredoc_input(fd, fd_std, limiter) < 0)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else if (pid)
	{
		*input_fd = wait_heredoc_input(fd, pid);
		if (*input_fd < 0)
			return (ERROR);
	}
	return (0);
}
