/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:52:26 by heson             #+#    #+#             */
/*   Updated: 2023/03/22 17:58:55 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_cmd	*create_cmd_struct(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	new_cmd->ac = 0;
	new_cmd->av = 0;
	new_cmd->rd_in = 0;
	new_cmd->rd_out = 0;
	new_cmd->rd_heredoc = 0;
	new_cmd->rd_append = 0;
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
	if (target->rd_in)
		free(target->rd_in);
	if (target->rd_out)
		free(target->rd_out);
	if (target->rd_heredoc)
		free(target->rd_heredoc);
	if (target->rd_append)
		free(target->rd_append);
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
			set_cmd_av(*tk_lst, &(*cmd)->av, (*cmd)->ac);
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
				set_cmd_redirection(tk_p->content, tk_p->next->content, cmd);
				tk_p = tk_p->next;
			}
		}
		else
			(*cmd)->ac++;
		if (tk_p)
			tk_p = tk_p->next;
	}
}

t_list	*set_cmd_av(t_list *tk_p, char **av[], int ac)
{
	int	i;

	*av = (char **)ft_calloc((ac + 1), sizeof(char *));
	if (!*av)
		return (NULL);
	i = 0;
	while (i < ac && tk_p)
	{
		if (is_redirection((char *)tk_p->content))
			tk_p = tk_p->next;
		else
		{
			(*av)[i] = ft_strdup((char *)tk_p->content);
			if (!(*av)[i])
				return (NULL);
			i++;
		}
		if (tk_p)
			tk_p = tk_p->next;
	}
	return (tk_p);
}

void	set_cmd_redirection(char *type, char *val, t_cmd **cmd)
{
	if (*type == '<')
	{
		if ((*cmd)->rd_in)
			ft_free_str(&(*cmd)->rd_in);
		if ((*cmd)->rd_heredoc)
			ft_free_str(&(*cmd)->rd_heredoc);
		if (ft_strncmp(type, "<", 5) == 0)
			(*cmd)->rd_in = ft_strdup(val);
		else if (ft_strncmp(type, "<<", 5) == 0)
			(*cmd)->rd_heredoc = ft_strdup(val);
	}
	else if (*type == '>')
	{
		if ((*cmd)->rd_out)
			ft_free_str(&(*cmd)->rd_out);
		if ((*cmd)->rd_append)
			ft_free_str(&(*cmd)->rd_append);
		if (ft_strncmp(type, ">", 5) == 0)
			(*cmd)->rd_out = ft_strdup(val);
		else if (ft_strncmp(type, ">>", 5) == 0)
			(*cmd)->rd_append = ft_strdup(val);
	}
}
