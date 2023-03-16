/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:45:17 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/16 21:19:43 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
//토크나이징한거 struct에 넣기
//환경변수 변환
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

t_tk	*create_token(char *data, int is_env)
{
	t_tk	*ret;

	ret = (t_tk *)malloc(sizeof(t_tk));
	// null
	ret->data = data;
	ret->is_env = is_env;
	return (ret);
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

int	tokenizing(t_list **tk_lst, char *line)
{
	int quote;
	int	i;
	int	start_p;
	char	*token;
	int		token_size;
	int		tmp_i;
	int		is_env;

	i = 0;
	start_p = 0;
	quote = 0;
	is_env = 0;
	while(1)
	{
		is_env = 0;
		quote = is_quote(line[i], quote);
		if ((line[i] == ';' || line[i] == '\\') && quote == 0)
		{
			printf("test exit: %c\n", line[i]);
			return (ERROR);
		}
		if (quote == 0)// "" '' 닫혀있을때
		{
			if (line[i] == ' ' || line[i] == '|' ||
				line[i] == '<' || line[i] == '>' || line[i] == '\0')
			{
				if (start_p < i)
				{
					token = (char *)malloc(sizeof(char) * (i - start_p + 1));
					// null guard
					ft_strlcpy(token, &line[start_p], i - start_p + 1);
					if (ft_strchr(token, '$'))
						is_env = 1;
					ft_lstadd_back(tk_lst, ft_lstnew(create_token(token, is_env)));
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
					if (ft_strchr(token, '$'))
						is_env = 1;
					ft_lstadd_back(tk_lst, ft_lstnew(create_token(token, is_env)));
				}
				i += token_size;
				start_p = i;
			}
			else //char
				i++;
		}
		else// "" '' 안닫혀있음
		{
			tmp_i = i;
			i = tokenizing_quote(line, i, quote);
			if (start_p == tmp_i)
				token = (char *)malloc(sizeof(char) * (i - start_p));
			else
				token = (char *)malloc(sizeof(char) * (i - start_p + 1));
			// null guard
			if (start_p != tmp_i)
				ft_strlcpy(token, &line[start_p], tmp_i - start_p + 1);
			ft_strlcpy(token + (tmp_i - start_p), &line[tmp_i + 1], i - tmp_i);
			if (ft_strchr(token, '$') && quote != 1)
					is_env = 1;
			ft_lstadd_back(tk_lst, ft_lstnew(create_token(token, is_env)));
			i++;
			start_p = i;
			quote = 0;
		}
	}
	return (0);
}

int	parsing(char *line, t_cmd **cmd)
{
	t_list	*tk_lst;

	tk_lst = NULL;
	if (tokenizing(&tk_lst, line) < 0)
		return (ERROR);
	// tokenizing(&tk_lst, line);
	for (t_list *p = tk_lst; p; p = p->next) {
		printf("%s, %d\n", ((t_tk*)p->content)->data, ((t_tk*)p->content)->is_env);
	}
	
	return (0);
}