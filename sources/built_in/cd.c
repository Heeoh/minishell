/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:05:31 by heson             #+#    #+#             */
/*   Updated: 2023/03/25 02:05:37 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "built_in.h"
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

// error 출력 부분 bash 형태에 맞게 손 봐야함
//cd: HOME not set\n
//cd - -> $OLDPWD참조 -> 만약 없으면 "minishell: cd: HOME not set\n"
int	ft_cd(char *path, t_list *env_lst)
{
	char *old_pwd;
	// printf("from: %s\n", getcwd(0, 256));
	old_pwd = getcwd(NULL, 0);
	printf("minishell: cd: HOME not set");
	if (chdir(path) < 0)
	{
		if (access(path, F_OK) == -1)
			printf("minishell: cd: %s: No such file or directory\n", path);
		else if (access(path, X_OK) == -1)
			printf("cd: permission denied: %s", path);
		else
			printf("minishell: cd: %s: Not a directory", path);
		return (-1);
	}
	else
		set_env_pwd(old_pwd, env_lst);
	free(old_pwd);
    // printf("to: %s\n", getcwd(0, 256));
	return (0);
}

// int main(int ac, char *av[]) {
// 	if (ac != 2)
// 		return (1);
// 	if (ft_cd(av[1]) < 0)
// 		return (1);
// }