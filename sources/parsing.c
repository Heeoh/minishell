/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:45:17 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/21 20:26:55 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
//unset(환경변수 지우기)
//exit
// >< 
//built in func
//built in 이랑 실행부 연결
//awk
//export
//momory leak

void	ft_free_str(char **arg)
{
	if (arg && *arg)
		free(*arg);
	*arg = NULL;
}

char	*strjoin_n_free(char *s1, char *s2)
{
	char	*ret;

	ret = NULL;
	if (!s1 && !s2)
		return (ret);
	if (s1 && s2)
	{
		ret = ft_strjoin(s1, s2);
		if (!ret)
			return (NULL);
		ft_free_str(&s1);
		ft_free_str(&s2);
	}
	else if (!s1)
		ret = ft_strdup(s2);
	else if (!s2)
		ret = ft_strdup(s1);
	return (ret);
}

char	*ft_strndup(const char *str, size_t size)
{
	char			*ret;
	char			*strp;
	unsigned int	i;

	ret = (char *)malloc(size + 1);
	if (!ret)
		return (NULL);
	i = 0;
	strp = (char *)str;
	while (strp && *strp && i < size)
		ret[i++] = *strp++;
	ret[i] = '\0';
	return (ret);
}

int	is_redirection(char *arg)
{
	if (ft_strncmp(arg, "<", 5) == 0
		|| ft_strncmp(arg, ">", 5) == 0
		|| ft_strncmp(arg, "<<", 5) == 0
		|| ft_strncmp(arg, ">>", 5) == 0)
		return (1);
	return (0);
}

t_list	*init_cmd_av(t_list *tk_p, char **av[], int ac)
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

int	init_cmd_val(t_list **tk_lst, t_cmd **cmd)
{
	t_list	*tk_p;

	*cmd = create_cmd_struct();
	tk_p = *tk_lst;
	while (1)
	{
		if (!tk_p || ft_strncmp(tk_p->content, "|", 5) == 0)
		{
			init_cmd_av(*tk_lst, &(*cmd)->av, (*cmd)->ac);
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

int	init_cmd_lst(t_list **cmd, t_list *tk_lst)
{
	t_list	*tk_p;
	t_cmd	*new_cmd;

	tk_p = tk_lst;
	new_cmd = NULL;
	while (tk_p)
	{
		if (init_cmd_val(&tk_p, &new_cmd) < 0)
			return (ERROR);
		ft_lstadd_back(cmd, ft_lstnew(new_cmd));
		if (tk_p)
			tk_p = tk_p->next;
	}
	return (0);
}

int	parsing(char *line, t_list **cmd, t_list *env_lst)
{
	t_list	*tk_lst;

	tk_lst = NULL;
	if (tokenizing(&tk_lst, line, env_lst) < 0)
		return (ERROR);
	// for (t_list *p = tk_lst; p; p = p->next)
	// 	printf("%s\n", (char *)p->content);
	init_cmd_lst(cmd, tk_lst);
	ft_lstclear(&tk_lst, free);
	return (0);
}

// int main(int ac, char *av[], char *env[])
// {
// 	t_list	*cmds;

// 	ac = 0;
// 	av = 0;
// 	t_list *envlst = init_env(env);
// 	cmds = NULL;
// 	parsing("<<end cat > out | echo $USER | echo 'hello'", &cmds, envlst);
// 	for (t_list *p = cmds; p; p=p->next) {
// 		for (int i=0; i<((t_cmd *)p->content)->ac; i++) {
// 			printf("%s, ", ((t_cmd *)p->content)->av[i]);
// 		}
// 		printf("\n");
// 		printf("in: %s, out: %s, heredoc: %s, append: %s\n", ((t_cmd *)p->content)->rd_in, ((t_cmd *)p->content)->rd_out, ((t_cmd *)p->content)->rd_heredoc, ((t_cmd *)p->content)->rd_append);
// 	}
// }
