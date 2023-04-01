/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:19:42 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:38:54 by jkim3            ###   ########.fr       */
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
