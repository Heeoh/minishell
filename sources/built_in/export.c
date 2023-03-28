/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:19:42 by heson             #+#    #+#             */
/*   Updated: 2023/03/28 17:01:53 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int ft_export(t_cmd *cmd, t_list *env_lst)
{
	char	**p;
	t_list	*sorted;
	
	if (cmd->ac == 1) // 전체 출력
	{
		sorted = ft_lstmap(env_lst, copy_env_var, free_env_var);
		sort_env_lst(&sorted);
		print_env_lst(sorted, 0);
		ft_lstclear(&sorted, free_env_var);
	}
	else // 추가
	{
		p = &(cmd->av[1]);
		while (p && *p)
		{
			if (ft_putenv(env_lst, *p) < 0)
			{
				printf("minishell: export: '%s': not a valid identifier\n", *p);
				return (EXIT_FAILURE);
			}
			p++;
		}
	}
	return (EXIT_SUCCESS);
}

// int main(int ac, char *av[], char *env[]){

// 	t_list	*mini_env;
// 	t_cmd	*cmd;

// 	cmd = create_cmd_struct();
// 	cmd->ac = 3;
// 	cmd->av = (char **)malloc(sizeof(char *) * (cmd->ac + 1));
// 	cmd->av[0] = ft_strdup("export");
// 	cmd->av[1] = ft_strdup("water=jj");
// 	cmd->av[2] = ft_strdup("water=삼다수");
// 	cmd->av[cmd->ac] = 0;
// 	mini_env = init_env_lst(env);
// 	ft_export(cmd, mini_env);
// 	cmd->ac = 1;
// 	ft_export(cmd, mini_env);
	
// 	// print_env_lst(mini_env);
// 	// printf("%s\n", getenv("water"));
// 	// ft_export("water=삼다수");
// 	// printf("%s\n", getenv("water"));
// }