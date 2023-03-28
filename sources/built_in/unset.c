/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:24:02 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/28 21:53:43 by heson            ###   ########.fr       */
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

void	del_key_front(t_list *tmp, t_list *p, t_list **env_lst)
{
	tmp = p;
	*env_lst = p->next;
	ft_lstdelone(tmp, free_env_var);
}

void	del_key(t_list *tmp, t_list *p)
{
	tmp = p->next;
	p->next = p->next->next;
	ft_lstdelone(tmp, free_env_var);
}

int	ft_unset(t_cmd *cmd, t_list **env_lst)
{
	int		i;
	t_list	*p;
	t_list	*tmp;

	tmp = 0;
	p = *env_lst;
	i = 1;
	while (cmd->av[i] && is_key(cmd->av[i]))
	{
		if (ft_strncmp(cmd->av[i], ((t_env_var *)(*env_lst)->content)->key,
			1000) == 0 && ft_strncmp(cmd->av[i], "_", 5) != 0)
		{
			del_key_front(tmp, p, env_lst);
			return (EXIT_SUCCESS);
		}
		while (p && p->next)
		{
			if (ft_strncmp(cmd->av[i], ((t_env_var *)p->next->content)->key,
					1000) == 0)
				del_key(tmp, p);
			p = p->next;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
