/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:19:42 by heson             #+#    #+#             */
/*   Updated: 2023/03/30 19:10:46 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_export(t_cmd *cmd, t_list *env_lst)
{
	char	**p;
	t_list	*sorted;

	if (cmd->ac == 1)
	{
		sorted = ft_lstmap(env_lst, copy_env_var, free_env_var);
		sort_env_lst(&sorted);
		print_env_lst(sorted, 0);
		ft_lstclear(&sorted, free_env_var);
	}
	else
	{
		p = &(cmd->av[1]);
		while (p && *p)
		{
			if (ft_putenv(env_lst, *p) < 0)
				return (per_n_ret("export", *p, "not a valid identifier", 1));
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