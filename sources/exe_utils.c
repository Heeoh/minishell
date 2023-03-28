/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:06:24 by heson             #+#    #+#             */
/*   Updated: 2023/03/29 03:33:30 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

#include <signal.h>


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

// void sig_han(int sig)
// {
// 	if (sig != SIGINT)
// 		return ;
// 	ft_putendl_fd("sigint handler of heredoc", 2);
// 	exit(1);
// }

int	do_heredoc(char *limiter, int *input_fd, int fd_stdin)
{
	int		fd[2];
	// int		pid;
	char	*line;
	// int		status;

	fd[R_FD] = -1;
	fd[W_FD] = -1;
	line = 0;
	if (pipe(fd) == -1)
		return (perror_n_return("pipe error", 0, EXIT_FAILURE));
	while (1)
	{
		write(2, "> ", 2); // stdout으로 하면 파이프에서 히어독 안됨, 근데... ls 전에도 같이 나와...
		line = get_next_line(fd_stdin);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) - 1) == 0)
			break ;
		ft_putstr_fd(line, fd[W_FD]);
	}
	close(fd[W_FD]);
	*input_fd = fd[R_FD];
	// pid = fork();
	// if (pid == -1)
	// 	return (perror_n_return("fork error", 0, EXIT_FAILURE));	
	// else if (!pid)
	// {
	// 	// signal(SIGINT, SIG_DFL);
	// 	close(fd[R_FD]);
	// 	while (1)
	// 	{
	// 		write(STDOUT_FILENO, "> ", 2);
	// 		line = get_next_line(fd_stdin);
	// 		if (!line)
	// 			break ;
	// 		if (ft_strncmp(line, limiter, ft_strlen(limiter) - 1) == 0)
	// 			break ;
	// 		ft_putstr_fd(line, fd[W_FD]);
	// 	}
	// 	close(fd[W_FD]);
	// 	exit(0);
	// }
	// else if (pid)
	// {
	// 	close(fd[W_FD]);
	// 	ft_putnbr_fd(pid, 2);
	// 	write(2, "\n", 1);
	// 	ft_putnbr_fd(waitpid(pid, &status, 0), 2);
	// 	write(2, "\n\n", 2);
	// 	if (WIFSIGNALED(status))
	// 	{
	// 		// ft_putstr_fd("sigint", 2);
	// 		if (WTERMSIG(status) == 2)
	// 		{
	// 			ft_putendl_fd("sigint", 2);
	// 			exit(1);
	// 		}
	// 		else
	// 			exit(1);
	// 	}
	// 	else if (WIFEXITED(status))
	// 		*input_fd = fd[R_FD];
	// }
	return (0);
}

int	do_redirection_in(char *val, int *fd, char is_heredoc, int fd_stdin)
{
	if (is_heredoc)
	{
		if (do_heredoc(val, fd, fd_stdin) < 0)
			return (ERROR);
	}
	else
	{
		*fd = open(val, O_RDONLY, 0644);
		if (*fd < 0)
			return (perror_n_return(val, 0, EXIT_FAILURE));
	}
	if (dup2(*fd, STDIN_FILENO) < 0)
		return (perror_n_return(NULL, 0, EXIT_FAILURE));
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
		return (perror_n_return(NULL, 0, EXIT_FAILURE));
	return (0);
}
