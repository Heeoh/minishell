/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:24:02 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/24 20:03:25 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_key(char *av)
{
	int	i;

	i = 0;
	if (!ft_isalpha(av[i]) && av[i] != '_')
	{
		printf("minishell: unset: `%s': not a valid identifier\n", av);
		return (0);
	}
	i++;
	while (av[i])
	{
		if (!ft_isalnum(av[i]) && av[i] != '_')
		{
			printf("minishell: unset: `%s': not a valid identifier\n", av);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_cmd *cmd, t_list **env_lst)
{
	int		i;
	t_list	*p;
	t_list	*tmp;

	p = *env_lst;
	i = 1;
	while (cmd->av[i] && is_key(cmd->av[i]))
	{
		if (ft_strncmp(cmd->av[i], ((t_env_var *)(*env_lst)->content)->key,
			1000) == 0 && ft_strncmp(cmd->av[i], "_", 5) != 0)
		{
			tmp = p;
			*env_lst = p->next;
			ft_lstdelone(tmp, free_env_var);
			return (0);
		}
		while (p && p->next)
		{
			if (ft_strncmp(cmd->av[i], ((t_env_var *)p->next->content)->key, 1000) == 0)
			{
				tmp = p->next;
				p->next = p->next->next;
				ft_lstdelone(tmp, free_env_var);
			}
			p = p->next;
		}
		i++;
	}
	return (0);
}

// int main(int ac, char *av[], char *env[]){
//     t_list  *mini_env;
//     mini_env = init_env(env);
//      ft_putenv(mini_env, "kkk=a");
// 	 print_env_lst(mini_env, 1);
// 	ft_unset("fdjkl", &mini_env);
// 	printf("\n\n\n\n");
//     print_env_lst(mini_env, 1);
// }