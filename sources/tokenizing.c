/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:36:09 by heson             #+#    #+#             */
/*   Updated: 2023/03/20 18:15:42 by heson            ###   ########.fr       */
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

char	*tokenizing_quote(char *start_p, int quote)
{
	char	*p;

	p = start_p + 1;
	while (is_quote(*p, quote))
	{
		if (!*p)
		{
			printf("quote error : not closed quote\n");
			return (NULL);
		}
		p++;
	}
	return (p);
}

int	is_token_separator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>' || c == '\0')
		return (1);
	return (0);
}

int	ch_exc(char c)
{
	printf("'%c': not a valid character\n", c);
	return (-1);
}

int	tokenizing(t_list **tk_lst, char *line, t_list *env_lst)
{
	int		quote;
	char	*start_p;
	char	*token;
	int		token_size;

	// i = 0;
	start_p = line;
	quote = 0;
	token = NULL;
	token_size = 0;
	while (1)
	{
		quote = is_quote(*line, quote);
		if (quote == 0) // "" '' 닫혀있을때
		{
			if (*line == ';' || *line == '\\')
				return (ch_exc(*line));
			if (is_token_separator(*line))
			{
				if (token_size || start_p < line)
				{
					token = get_token(start_p, line, quote, env_lst, token);
					ft_lstadd_back(tk_lst, ft_lstnew(token));
				}
				if (!*line)
					break ;
				token_size = 1;
				if (*line != ' ')
				{
					if ((*line == '<' || *line == '>')
						&& *line == *(line + 1))
						token_size++;
					token = ft_strndup(line, token_size);
					ft_lstadd_back(tk_lst, ft_lstnew(token));
				}
				line += token_size;
				start_p = line;
				token = NULL;
				token_size = 0;
			}
			else // char
				line++;
		}
		else// "" '' 안닫혀있음
		{
			token = get_token(start_p, line, quote, env_lst, token);
			start_p = line;
			line = tokenizing_quote(line, quote);
			if (!line)
				return (ERROR);
			token = get_token(start_p + 1, line - 1, quote, env_lst, token);
			token_size = ft_strlen(token);
			start_p = line;
			quote = 0;
		}
	}
	return (0);
}
