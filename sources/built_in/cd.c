/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:05:31 by heson             #+#    #+#             */
/*   Updated: 2023/03/31 17:51:54 by heson            ###   ########.fr       */
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

#include <errno.h>

void	cd_error_print(char *path)
{
	// printf("%d\n", errno);
	// if (access(path, F_OK) == -1) // errno 2
	// 	per_n_ret("cd", path, "No such file or directory", 1);
	// else if (access(path, X_OK) == -1) //errno 13
	// 	per_n_ret("cd", path, "Permission denied", 1);
	// else // errno 2
	// {
		// path = 0;
		perror_n_return("cd", path, 0, EXIT_FAILURE);
	// }
		
		// per_n_ret("cd", path, "Not a directory", 1);
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
	// !old_pwd error
	if (chdir(path) < 0)
	{
		perror_n_return("cd", path, 0, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	else
		set_env_pwd(old_pwd, env_lst);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
