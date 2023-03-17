/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:45:17 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/17 21:54:33 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
//토크나이징한거 struct에 넣기 - done
//norm
//built in func
//built in 이랑 실행부 연결
//signal 실행부
//awk
//momory leak


int	is_quote(char q, int quote)
{
	if (q == '\'')
	{
		if (quote == 1)
			return (0);
		else if (quote == 2)
			return (2);
		else
			return (1);
	}
	else if (q == '\"')
	{
		if (quote == 2)
			return (0);
		else if (quote == 1)
			return (1);
		else
			return (2);
	}
	return (quote);
}

int	tokenizing_quote(char *line, int start_p, int quote)
{
	int n;
	n = start_p + 1;
	while (is_quote(line[n], quote))
	{
		if (!line[n])
		{
			printf("quote error : not closed quote\n");
			return (ERROR);
		}
		n++;
	}
	return (n);
}

char	*strjoin_n_free(char *s1, char *s2)
{
	char	*ret;

	if (s1 && s2)
	{
		ret = ft_strjoin(s1, s2);
		if (!ret)
			return (NULL);
		free(s1);
		free(s2);
	}
	if (!s1)
		ret = ft_strdup(s2);
	if (!s2)
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

int	tokenizing(t_list **tk_lst, char *line, t_list *env_lst)
{
	int quote;
	int	i;
	int	start_p;
	char	*token;
	int		token_size;
	char	*tmp;

	i = 0;
	start_p = 0;
	quote = 0;
	token = NULL;
	token_size = 0;
	while(1)
	{
		quote = is_quote(line[i], quote);
		if (quote == 0)// "" '' 닫혀있을때
		{
			if (line[i] == ';' || line[i] == '\\')
			{
				printf("test exit: %c\n", line[i]);
				return (ERROR);
			}
			if (line[i] == ' ' || line[i] == '|' ||
				line[i] == '<' || line[i] == '>' || line[i] == '\0')
			{
				if (token_size || start_p < i)
				{
					tmp = ft_strndup(line + start_p, i - start_p);
					if (ft_strchr(tmp, '$') && quote != 1)
						tmp = replace_env(env_lst, tmp);
					token = strjoin_n_free(token, tmp);
					// null guard
					ft_lstadd_back(tk_lst, ft_lstnew(token));
				}
				if (!line[i])
					break;
				token_size = 1;
				if (line[i] != ' ')
				{
					if ((line[i] == '<' || line[i] == '>')
						&& line[i] == line[i + 1])
						token_size++;
					token = (char *)malloc(sizeof(char) * token_size + 1);
					ft_strlcpy(token, &line[i], token_size + 1);
					ft_lstadd_back(tk_lst, ft_lstnew(token));
				}
				i += token_size;
				start_p = i;
				token = NULL;
				token_size = 0;
			}
			else // char
				i++;
		}
		else// "" '' 안닫혀있음
		{
			tmp = ft_strndup(line + start_p, i - start_p);
			token = strjoin_n_free(token, tmp);
			start_p = i;
			i = tokenizing_quote(line, i, quote);
			if (i < 0)
				return (ERROR);
			tmp = ft_strndup(line + start_p + 1, i - start_p - 1);
			if (ft_strchr(tmp, '$') && quote != 1)
				tmp = replace_env(env_lst, tmp);
			token = strjoin_n_free(token, tmp);
			token_size = ft_strlen(token);
			i++;
			start_p = i;
			quote = 0;
		}
	}
	return (0);
}

int	init_cmd_av(t_list *tk_lst, char **av[], int ac)
{
	t_list	*tk_p;
	int		i;

	*av = (char **)malloc(sizeof(char *) * (ac + 1));
	if (!*av)
		return (ERROR);
	i = 0;
	tk_p = tk_lst;
	while (i < ac)
	{
		if (ft_strncmp(tk_p->content, "<", 5) == 0
			|| ft_strncmp(tk_p->content, ">", 5) == 0
			|| ft_strncmp(tk_p->content, "<<", 5) == 0
			|| ft_strncmp(tk_p->content, ">>", 5) == 0)
		{
			tk_p = tk_p->next;
			if (tk_p)
				tk_p = tk_p->next;
		}
		else
		{
			(*av)[i] = ft_strdup((char *)tk_p->content);
			if (!(*av)[i])
				return (ERROR);
			i++;
			tk_p = tk_p->next;
		}
	}
	return (0);
}

t_list	*init_cmd_val(t_list *tk_lst, t_cmd **cmd)
{
	t_list	*tk_p;

	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	(*cmd)->ac = 0;
	(*cmd)->av = 0;
	(*cmd)->rd_in = 0;
	(*cmd)->rd_out = 0;
	(*cmd)->rd_heredoc = 0;
	(*cmd)->rd_append = 0;
	tk_p = tk_lst;
	while (1)
	{
		if (!tk_p || ft_strncmp(tk_p->content, "|", 5) == 0)
		{
			init_cmd_av(tk_lst, &(*cmd)->av, (*cmd)->ac);
			return (tk_p);
		}
		if (ft_strncmp(tk_p->content, "<", 5) == 0 && tk_p->next)
		{
			(*cmd)->rd_in = ft_strdup((char *)tk_p->next->content);
			tk_p = tk_p->next;
		}
		else if (ft_strncmp(tk_p->content, ">", 5) == 0 && tk_p->next)
		{
			(*cmd)->rd_out = ft_strdup((char *)tk_p->next->content);
			tk_p = tk_p->next;
		}
		else if (ft_strncmp(tk_p->content, "<<", 5) == 0 && tk_p->next)
		{
			(*cmd)->rd_heredoc = ft_strdup((char *)tk_p->next->content);
			tk_p = tk_p->next;
		}
		else if (ft_strncmp(tk_p->content, ">>", 5) == 0 && tk_p->next)
		{
			(*cmd)->rd_append = ft_strdup((char *)tk_p->next->content);
			tk_p = tk_p->next;
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
		tk_p = init_cmd_val(tk_lst, &new_cmd);
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
	init_cmd_lst(cmd, tk_lst);
	
	return (0);
}

// int main(int ac, char *av[], char *env[])
// {
// 	t_list	*cmds;

// 	ac = 0;
// 	av = 0;
// 	t_list *envlst = init_env(env);
// 	cmds = NULL;
// 	parsing("$USER", &cmds, envlst);
// }
