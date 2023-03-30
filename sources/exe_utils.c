/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:06:24 by heson             #+#    #+#             */
/*   Updated: 2023/03/30 18:05:42 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "mini_utils.h"
#include <signal.h>

char	*find_path(char *cmd, t_list *env)
{
	char	*dir;
	char	*ret;
	char	**path_group;
	int		i;
	char	*path_env;

	ret = 0;
	path_env = 0;
	path_env = ft_getenv(env, "PATH");
	if (!path_env)
		return (NULL);
	path_group = ft_split(path_env, ':');
	if (!path_group)
		exit(1);
	i = -1;
	while (path_group[++i])
	{
		dir = ft_strjoin(path_group[i], "/");
		if (!dir)
			exit(1);
		ret = ft_strjoin(dir, cmd);
		if (!ret)
			exit(1);
		free(dir);
		if (access(ret, F_OK) == 0)
			break ;
		free(ret);
	}
	i = -1;
	while (path_group[++i])
		free(path_group[i]);
	free(path_group);
	return (ret);
}

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
	return (0);
}

int	wait_heredoc_input(int fd[], int child_pid)
{
	int	status;

	close(fd[W_FD]);
	if (waitpid(child_pid, &status, 0) < 0)
		return (perror_n_return("waitpid", 0, 0, EXIT_FAILURE));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			ft_putstr_fd("\n", 2);
			g_exit_status = 1;
			return (ERROR);
		}
	}
	else if (WIFEXITED(status))
		return (fd[R_FD]);
	return (ERROR);
}

int	do_heredoc(char *limiter, int *input_fd, int fd_std[])
{
	int		fd[2];
	int		pid;
	char	*line;

	// signal(SIGINT, SIG_IGN);
	fd[R_FD] = -1;
	fd[W_FD] = -1;
	line = 0;
	if (pipe(fd) == -1)
		return (perror_n_return("pipe", 0, 0, EXIT_FAILURE));
	pid = fork();
	if (pid == -1)
		return (perror_n_return("fork", 0, 0, EXIT_FAILURE));
	else if (!pid)
		exit(get_heredoc_input(fd, fd_std, limiter));
	else if (pid)
	{
		*input_fd = wait_heredoc_input(fd, pid);
		if (*input_fd < 0)
			return (ERROR);
	}
	return (0);
}

int	do_redirection_in(char *val, int *fd, char is_heredoc, int fd_std[])
{
	if (is_heredoc)
	{
		if (*fd < 0 && do_heredoc(val, fd, fd_std) < 0)
			return (ERROR);
	}
	else
	{
		*fd = open(val, O_RDONLY, 0644);
		if (*fd < 0)
			return (perror_n_return(val, 0, 0, EXIT_FAILURE));
	}
	if (dup2(*fd, STDIN_FILENO) < 0)
		return (perror_n_return("dup2", 0, 0, EXIT_FAILURE));
	return (0);
}

int	do_redirection_out(char *filename, int *fd, char is_append)
{
	if (is_append)
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
		return (perror_n_return(filename, 0, 0, EXIT_FAILURE));
	if (dup2(*fd, STDOUT_FILENO) < 0)
		return (perror_n_return("dup2", 0, 0, EXIT_FAILURE));
	return (0);
}
