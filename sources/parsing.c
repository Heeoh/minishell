/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:45:17 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/17 16:09:51 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
//토크나이징한거 struct에 넣기
//환경변수 변환, cannot found

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

char	*strnjoin(char *s1, int s1_size, char *s2, int s2_size)
{
	char	*ret;
	int		is_s1_free;
	int		is_s2_free;

	is_s1_free = 0;
	is_s2_free = 0;
	if (!s1)
		s1_size = 0;
	if (!s2)
		s2_size = 0;
	if (s1_size < 0)
	{
		s1_size = ft_strlen(s1);
		is_s1_free = 1;
	}
	if (s2_size < 0)
	{
		s2_size = ft_strlen(s2);
		is_s2_free = 1;
	}
	ret = (char *)malloc(s1_size + s2_size + 1);
	// null
	if (s1)
		ft_strlcpy(ret, s1, s1_size + 1);
	if (s2)
		ft_strlcpy(ret + s1_size, s2, s2_size + 1);
	if (s1 && is_s1_free)
		free(s1);
	if (s2 && is_s2_free)
		free(s2);
	return (ret);
}

// char	*strjoin_n_free(char *s1, char *s2)
// {
// 	char	*ret;

// 	ret = ft_strjoin(s1, s2);
// 	if (!ret)
// 		return (NULL);
// 	free(s1);
// 	free(s2);
// 	return (ret);
// }

int	tokenizing(t_list **tk_lst, char *line)
{
	int quote;
	int	i;
	int	start_p;
	char	*token;
	int		token_size;
	// int		tmp_i;
	int		is_env;

	i = 0;
	start_p = 0;
	quote = 0;
	is_env = 0;
	token = NULL;
	token_size = 0;
	while(1)
	{
		is_env = 0;
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
				// if (start_p < i)
				// {
				// 	token = (char *)malloc(sizeof(char) * (i - start_p + 1));
				// 	// null guard
				// 	ft_strlcpy(token, &line[start_p], i - start_p + 1);
				// 	if (ft_strchr(token, '$'))
				// 		is_env = 1;
				// 	ft_lstadd_back(tk_lst, ft_lstnew(create_token(token, is_env)));
				// }
				if (token_size || start_p < i)
				{
					token = strnjoin(token, -1, line + start_p, i - start_p);
					// null guard
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
					// if (ft_strchr(token, '$'))
					// 	is_env = 1;
					ft_lstadd_back(tk_lst, ft_lstnew(create_token(token, is_env)));
				}
				i += token_size;
				start_p = i;
				token = NULL;
				token_size = 0;
			}
			else //char
				i++;
		}
		else// "" '' 안닫혀있음
		{
			// tmp_i = i;
			// i = tokenizing_quote(line, i, quote);
			// if (start_p == tmp_i)
			// 	token = (char *)malloc(sizeof(char) * (i - start_p));
			// else
			// 	token = (char *)malloc(sizeof(char) * (i - start_p + 1));
			// // null guard
			// if (start_p != tmp_i)
			// 	ft_strlcpy(token, &line[start_p], tmp_i - start_p + 1);
			// ft_strlcpy(token + (tmp_i - start_p), &line[tmp_i + 1], i - tmp_i);
			// if (ft_strchr(token, '$') && quote != 1)
			// 		is_env = 1;
			// ft_lstadd_back(tk_lst, ft_lstnew(create_token(token, is_env)));
			token = strnjoin(token, -1, line + start_p, i - start_p);
			token_size += ft_strlen(token);
			start_p = i;
			i = tokenizing_quote(line, i, quote);
			if (i < 0)
				return (ERROR);
			token = strnjoin(token, -1, line + start_p + 1, i - start_p - 1);
			token_size += ft_strlen(token);
			if (ft_strchr(token, '$') && quote != 1)
				is_env = 1;
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

	cmd = 0;
	tk_lst = NULL;
	if (tokenizing(&tk_lst, line) < 0)
		return (ERROR);
	// tokenizing(&tk_lst, line);
	for (t_list *p = tk_lst; p; p = p->next) {
		printf("%d, %s\n", ((t_tk*)p->content)->is_env, ((t_tk*)p->content)->data);
	}
	
	return (0);
}

// int main()
// {
// 	t_cmd	*cmds;

// 	parsing("echo \'\"$USER\'", &cmds);
// }
	