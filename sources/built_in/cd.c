/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:05:31 by heson             #+#    #+#             */
/*   Updated: 2023/03/28 21:34:21 by jkim3            ###   ########.fr       */
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
	ft_putenv(env_lst, str);
	free(str);
	new_pwd = getcwd(NULL, 0);
	str = ft_strjoin("PWD=", new_pwd);
	free(str);
	ft_putenv(env_lst, new_pwd);
	free(new_pwd);
}

void	cd_error_print(char *path)
{
	if (access(path, F_OK) == -1)
		printf("minishell: cd: %s: No such file or directory\n", path);
	else if (access(path, X_OK) == -1)
		printf("minishell: cd: %s: Permission denied\n", path);
	else
		printf("minishell: cd: %s: Not a directory\n", path);
}

int	ft_cd(char *path, t_list *env_lst)
{
	char	*old_pwd;

	if (!path || (path && !*path) || (ft_strncmp(path, "~", 5) == 0))
	{
		path = ft_getenv(env_lst, "HOME");
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) < 0)
	{
		cd_error_print(path);
		return (EXIT_FAILURE);
	}
	else
		set_env_pwd(old_pwd, env_lst);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
