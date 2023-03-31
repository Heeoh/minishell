/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:06:24 by heson             #+#    #+#             */
/*   Updated: 2023/03/31 19:18:14 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "mini_utils.h"
#include <signal.h>

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

char	*get_full_path(char *path_group, char *cmd)
{
	char	*dir;
	char	*path;

	dir = ft_strjoin(path_group, "/");
	if (!dir)
		exit(1);
	path = ft_strjoin(dir, cmd);
	if (!path)
		exit(1);
	free(dir);
	return (path);
}

char	*find_path(char *cmd, t_list *env)
{
	char	*path;
	char	**path_group;
	int		i;
	char	*path_env;

	path_env = ft_getenv(env, "PATH");
	if (!path_env)
		return (NULL);
	path_group = ft_split(path_env, ':');
	if (!path_group)
		exit(1);
	i = -1;
	while (path_group[++i])
	{
		path = get_full_path(path_group[i], cmd);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
	}
	ft_free_2d_arr(path_group);
	return (path);
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

int	do_redirection_in(char *val, int *fd, char is_heredoc)
{
	if (!is_heredoc)
		*fd = open(val, O_RDONLY, 0644);
	if (*fd < 0)
		return (perror_n_return(val, 0, 0, EXIT_FAILURE));
	if (dup2(*fd, STDIN_FILENO) < 0)
		return (perror_n_return("dup2kkkk", 0, 0, EXIT_FAILURE));
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
