/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:24:02 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/21 22:07:35 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_unset(char *key, t_list **env_lst)
{
	t_list	*p;
	t_list	*tmp;

	p = *env_lst;
	if (ft_strncmp(key, ((t_env_var *)(*env_lst)->content)->key, 1000) == 0)
	{
		tmp = p;
		*env_lst = p->next;
		ft_lstdelone(tmp, free_env_var);
		return (0);
	}
	while (p && p->next)
	{
		if (ft_strncmp(key, ((t_env_var *)p->next->content)->key, 1000) == 0)
		{
			tmp = p->next;
			p->next = p->next->next;
			ft_lstdelone(tmp, free_env_var);
		}
		p = p->next;
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
