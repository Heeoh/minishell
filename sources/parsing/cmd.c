/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:52:26 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 19:26:24 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/mini_parsing.h"

int	set_cmd_val(t_list **tk_lst, t_cmd **cmd)
{
	t_list	*tk_p;

	*cmd = create_cmd_struct();
	tk_p = *tk_lst;
	if (ft_strncmp(tk_p->content, "|", 5) == 0)
		return (perror_n_return("syntax error", "unexpected token", 1, 258));
	while (1)
	{
		if (!tk_p || ft_strncmp(tk_p->content, "|", 5) == 0)
			return (set_cmd_pipe(tk_lst, tk_p, cmd));
		else if (is_redirection((char *)tk_p->content))
		{
			if (!tk_p->next || is_redirection((char *)tk_p->next->content))
				return (perror_n_return("syntax error",
						"unexpected token", 1, 258));
			if (set_cmd_redirection(tk_p->content,
					tk_p->next->content, &(*cmd)->rd) < 0)
				return (ERROR);
			tk_p = tk_p->next;
		}
		else
			(*cmd)->ac++;
		if (tk_p)
			tk_p = tk_p->next;
	}
}

int	set_cmd_av(t_list *tk_p, char **av[], int ac)
{
	int	i;

	*av = (char **)ft_calloc((ac + 1), sizeof(char *));
	if (!*av)
		return (ERROR);
	i = 0;
	while (i < ac && tk_p)
	{
		if (is_redirection((char *)tk_p->content))
			tk_p = tk_p->next;
		else
		{
			(*av)[i] = ft_strdup((char *)tk_p->content);
			if (!(*av)[i])
				return (ERROR);
			i++;
		}
		if (tk_p)
			tk_p = tk_p->next;
	}
	return (0);
}

int	set_cmd_redirection(char *type, char *val, t_list **rd_lst)
{
	t_redirection	*new_rd;
	t_list			*new_node;

	new_rd = 0;
	if (ft_strncmp(type, "<", 5) == 0)
		new_rd = create_rd(RD_IN, val);
	else if (ft_strncmp(type, "<<", 5) == 0)
		new_rd = create_rd(RD_HEREDOC, val);
	else if (ft_strncmp(type, ">", 5) == 0)
		new_rd = create_rd(RD_OUT, val);
	else if (ft_strncmp(type, ">>", 5) == 0)
		new_rd = create_rd(RD_APPEND, val);
	if (!new_rd)
		return (ERROR);
	new_node = ft_lstnew(new_rd);
	if (!new_node)
		exit(1);
	ft_lstadd_back(rd_lst, new_node);
	return (0);
}

int	set_cmd_pipe(t_list **tk_lst, t_list *tk_p, t_cmd **cmd)
{
	if (tk_p && (!tk_p->next || (tk_p->next
				&& ft_strncmp(tk_p->next->content, "|", 5) == 0)))
		return (perror_n_return("syntax error",
				"unexpected token", 1, 258));
	if (set_cmd_av(*tk_lst, &(*cmd)->av, (*cmd)->ac) < 0)
		return (ERROR);
	*tk_lst = tk_p;
	return (0);
}
