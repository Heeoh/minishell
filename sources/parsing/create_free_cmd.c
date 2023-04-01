/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_free_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:18:37 by jkim3             #+#    #+#             */
/*   Updated: 2023/04/01 19:26:27 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/mini_parsing.h"

t_redirection	*create_rd(int type, char *val)
{
	t_redirection	*ret;

	ret = 0;
	if (!val)
		return (NULL);
	ret = (t_redirection *)malloc(sizeof(t_redirection));
	if (!ret)
		exit(1);
	ret->type = type;
	ret->val = ft_strdup(val);
	return (ret);
}

void	free_rd_struct(void *arg)
{
	free(((t_redirection *)arg)->val);
	free(arg);
}

t_cmd	*create_cmd_struct(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		exit(1);
	new_cmd->ac = 0;
	new_cmd->av = 0;
	new_cmd->rd = NULL;
	return (new_cmd);
}

void	free_cmd_struct(void *arg)
{
	t_cmd	*target;
	int		i;

	target = (t_cmd *)arg;
	i = 0;
	while (i < target->ac)
		free(target->av[i++]);
	ft_lstclear(&target->rd, free_rd_struct);
}
