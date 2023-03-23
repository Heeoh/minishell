/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:06:24 by heson             #+#    #+#             */
/*   Updated: 2023/03/22 17:37:10 by heson            ###   ########.fr       */
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

char	*create_heredoc_file(char *limiter)
{
	int		fd;
	char	*filename;
	char	*str;

	// open 시 이미 동일한 파일이 있을 경우 처리
	filename = ft_strdup("heredoc_tmp.txt");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		str = get_next_line(0);
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(fd, str, ft_strlen(str));
	}
	close(fd);
	return (filename);
}

int	do_redirection_in(char *val, int *fd, char is_heredoc)
{
	char	*filename;

	if (is_heredoc)
		filename = create_heredoc_file(val);
	else
		filename = val;
	*fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
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
