/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:06:24 by heson             #+#    #+#             */
/*   Updated: 2023/03/27 15:41:29 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*find_path(char *cmd, t_list *env)
{
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
	i = -1;
	while (path_group[++i])
	{
		ret = ft_strjoin(path_group[i], "/");
		ret = ft_strjoin(ret, cmd);
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

int	do_heredoc(char *limiter, int *input_fd)
{
	int		fd[2];
	int		pid;
	char	*line;

	fd[R_FD] = -1;
	fd[W_FD] = -1;
	line = 0;
	if (pipe(fd) == -1)
		return (perror_n_return("pipe error"));
	pid = fork();
	if (pid == -1)
		return (perror_n_return("fork error"));	
	else if (!pid)
	{
		close(fd[R_FD]);
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(line, limiter, ft_strlen(limiter) - 1) == 0)
				break ;
			ft_putstr_fd(line, fd[W_FD]);
		}
		close(fd[W_FD]);
		exit(0);
	}
	else if (pid)
	{
		close(fd[W_FD]);
		waitpid(pid, NULL, 0);
		*input_fd = fd[R_FD];
	}
	return (0);
}

int	do_redirection_in(char *val, int *fd, char is_heredoc, int std_fd[])
{
	// int	out_fd;

	if (is_heredoc)
	{
		// out_fd = dup(STDOUT_FILENO);
		dup2(std_fd[R_FD], STDIN_FILENO);
		// dup2(std_fd[W_FD], STDOUT_FILENO);
		if (do_heredoc(val, fd) < 0)
			return (perror_n_return("heredoc error"));
		// dup2(out_fd, STDOUT_FILENO);
	}
	else
		*fd = open(val, O_RDONLY, 0644);
	if (*fd < 0)
		return (perror_n_return("file open error"));
	if (dup2(*fd, STDIN_FILENO) < 0)
		return (perror_n_return("dup2 error"));
	return (0);
}

int	do_redirection_out(char *filename, int *fd, char is_append)
{
	close(*fd);
	if (is_append)
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(*fd, STDOUT_FILENO) < 0)
		return (perror_n_return("dup2 error"));
	return (0);
}
