/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:05:31 by heson             #+#    #+#             */
/*   Updated: 2023/03/31 20:07:51 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/built_in.h"
#include <unistd.h>
#include <stdio.h> // perror

void	set_env_pwd(char *old_pwd, t_list *env_lst)
{
	char	*str;
	char	*new_pwd;

	str = ft_strjoin("OLDPWD=", old_pwd);
	if (!str)
		exit(1);
	ft_putenv(env_lst, str);
	free(str);
	new_pwd = getcwd(NULL, 0);
	str = ft_strjoin("PWD=", new_pwd);
	if (!str)
		exit(1);
	free(new_pwd);
	ft_putenv(env_lst, str);
	free(str);
}

int	ft_cd(char *path, t_list *env_lst)
{
	char	*old_pwd;

	if (!path || (path && !*path) || (ft_strncmp(path, "~", 5) == 0))
	{
		path = ft_getenv(env_lst, "HOME");
		if (!path)
			return (perror_n_return("cd", "HOME not set", 1, 1));
	}
	if (ft_strncmp(path, "-", 5) == 0)
	{
		path = ft_getenv(env_lst, "OLDPWD");
		if (!path)
			return (perror_n_return("cd", "OLDPWD not set", 1, 1));
		printf("%s\n", path);
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd && ft_strncmp(path, ".", 5) == 0)
		perror_n_return("cd", "getcwd: cannot access parent directories",
			0, EXIT_FAILURE);
	if (chdir(path) < 0)
		return (perror_n_return("cd", path, 0, EXIT_FAILURE));
	else
		set_env_pwd(old_pwd, env_lst);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
