/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:52:26 by heson             #+#    #+#             */
/*   Updated: 2023/03/24 03:10:18 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../library/libft/libft.h"

t_redirection	*create_rd(int type, char *val)
{
	t_redirection	*ret;

	ret = 0;
	if (!val)
		return (NULL);
	ret = (t_redirection *)malloc(sizeof(t_redirection));
	if (!ret)
		return (NULL);
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

int	set_cmd_val(t_list **tk_lst, t_cmd **cmd)
{
	t_list	*tk_p;

	*cmd = create_cmd_struct();
	tk_p = *tk_lst;
	while (1)
	{
		if (!tk_p || ft_strncmp(tk_p->content, "|", 5) == 0)
		{
			if (set_cmd_av(*tk_lst, &(*cmd)->av, (*cmd)->ac) < 0)
				return (ERROR);
			*tk_lst = tk_p;
			return (0);
		}
		else if (is_redirection((char *)tk_p->content))
		{
			if (!tk_p->next)
			{
				perror_n_return("syntax error");
				return (ERROR);
			}
			else if (!is_redirection((char *)tk_p->next->content))
			{
				if (set_cmd_redirection(tk_p->content, tk_p->next->content, &(*cmd)->rd) < 0)
					return (ERROR);
				tk_p = tk_p->next;
			}
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
	ft_lstadd_back(rd_lst, new_node);
	return (0);
	// if (*type == '<')
	// {
	// 	if ((*cmd)->rd_in)
	// 		ft_free_str(&(*cmd)->rd_in);
	// 	if ((*cmd)->rd_heredoc)
	// 		ft_free_str(&(*cmd)->rd_heredoc);
	// 	if (ft_strncmp(type, "<", 5) == 0)
	// 		(*cmd)->rd_in = ft_strdup(val);
	// 	else if (ft_strncmp(type, "<<", 5) == 0)
	// 		(*cmd)->rd_heredoc = ft_strdup(val);
	// }
	// else if (*type == '>')
	// {
	// 	if ((*cmd)->rd_out)
	// 		ft_free_str(&(*cmd)->rd_out);
	// 	if ((*cmd)->rd_append)
	// 		ft_free_str(&(*cmd)->rd_append);
	// 	if (ft_strncmp(type, ">", 5) == 0)
	// 		(*cmd)->rd_out = ft_strdup(val);
	// 	else if (ft_strncmp(type, ">>", 5) == 0)
	// 		(*cmd)->rd_append = ft_strdup(val);
	// }
}
