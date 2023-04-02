/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:23:52 by heson             #+#    #+#             */
/*   Updated: 2023/04/02 16:32:57 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"
#include <sys/stat.h>

static char	*cmd_tolower(char *cmd)
{
	char	*lower_cmd;
	int		i;

	lower_cmd = ft_strndup(cmd, ft_strlen(cmd));
	i = 0;
	while (cmd[i])
	{
		lower_cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	return (lower_cmd);
}

int	is_built_in(char *cmd)
{
	char	*lower_cmd;
	int		ret;

	if (!cmd || !*cmd)
		return (-1);
	lower_cmd = cmd_tolower(cmd);
	ret = -1;
	if (ft_strncmp("echo", lower_cmd, 10) == 0)
		ret = BI_ECHO;
	if (ft_strncmp("env", lower_cmd, 10) == 0)
		ret = BI_ENV;
	if (ft_strncmp("pwd", lower_cmd, 10) == 0)
		ret = BI_PWD;
	if (ft_strncmp("exit", cmd, 10) == 0)
		ret = BI_EXIT;
	if (ft_strncmp("cd", cmd, 10) == 0)
		ret = BI_CD;
	if (ft_strncmp("unset", cmd, 10) == 0)
		ret = BI_UNSET;
	if (ft_strncmp("export", cmd, 10) == 0)
		ret = BI_EXPORT;
	ft_free_str(&lower_cmd);
	return (ret);
}

static char	*get_full_path(char *path_group, char *cmd)
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

static char	*find_path(char *cmd, t_list *env)
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
		ft_free_str(&path);
	}
	ft_free_2d_arr(path_group);
	return (path);
}

int	find_cmd_path(char *cmd, t_list *env, char **path)
{
	struct stat	st;

	if (!cmd || !*cmd)
		return (0);
	*path = find_path(cmd, env);
	if (!*path)
		*path = ft_strndup(cmd, ft_strlen(cmd));
	if (access(*path, F_OK) != 0)
		return (perror_n_return(cmd, "Command not found", 1, 127));
	stat(*path, &st);
	if (S_ISDIR(st.st_mode))
		return (perror_n_return(cmd, "Is a directory", 0, 126));
	if (access(*path, X_OK) != 0)
		return (perror_n_return(cmd, 0, 0, 126));
	return (0);
}
