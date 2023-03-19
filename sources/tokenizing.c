/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:36:09 by heson             #+#    #+#             */
/*   Updated: 2023/03/19 03:04:56 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

char	*get_token(char	*sp, char *ep, int quote, t_list *env_lst, char *tk)
{
	char	*tmp;
	char	*new_token;

	new_token = NULL;
	tmp = ft_strndup(sp, ep - sp);
	if (ft_strchr(tmp, '$') && quote != 1)
		tmp = replace_env(env_lst, tmp);
	new_token = strjoin_n_free(tk, tmp);
	return (new_token);
}

int	tokenizing_quote(char *line, int start_p, int quote)
{
	int	n;

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

int	tokenizing(t_list **tk_lst, char *line, t_list *env_lst)
{
	int		quote;
	int		i;
	int		start_p;
	char	*token;
	int		token_size;

	i = 0;
	start_p = 0;
	quote = 0;
	token = NULL;
	token_size = 0;
	while (1)
	{
		quote = is_quote(line[i], quote);
		if (quote == 0) // "" '' 닫혀있을때
		{
			if (line[i] == ';' || line[i] == '\\')
			{
				printf("'%c': not a valid character\n", line[i]);
				return (ERROR);
			}
			if (line[i] == ' ' || line[i] == '|'
				|| line[i] == '<' || line[i] == '>' || line[i] == '\0')
			{
				if (token_size || start_p < i)
				{
					token = get_token(line + start_p, &line[i], quote, env_lst, token);
					ft_lstadd_back(tk_lst, ft_lstnew(token));
				}
				if (!line[i])
					break ;
				token_size = 1;
				if (line[i] != ' ')
				{
					if ((line[i] == '<' || line[i] == '>')
						&& line[i] == line[i + 1])
						token_size++;
					token = ft_strndup(line + i, token_size);
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
			token = get_token(line + start_p, &line[i], quote, env_lst, token);
			start_p = i;
			i = tokenizing_quote(line, i, quote);
			if (i < 0)
				return (ERROR);
			token = get_token(line + start_p + 1, &line[i - 1], quote, env_lst, token);
			token_size = ft_strlen(token);
			i++;
			start_p = i;
			quote = 0;
		}
	}
	return (0);
}
