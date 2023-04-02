/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:12:54 by heson             #+#    #+#             */
/*   Updated: 2023/04/02 18:02:55 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/mini_parsing.h"

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

int	is_token_separator(char c)
{
	if (9 <= c && c <= 13)
		return (1);
	if (c == ' ' || c == '|' || c == '<' || c == '>' || c == '\0')
		return (1);
	return (0);
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

t_tokenizer	*init_tokenizer(char *line)
{
	t_tokenizer	*tokenizer;

	tokenizer = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (!tokenizer)
		exit(1);
	tokenizer->line = line;
	tokenizer->sp = line;
	tokenizer->quote = 0;
	tokenizer->tk_content = NULL;
	tokenizer->tk_size = 0;
	return (tokenizer);
}

void	free_tokenizer(t_tokenizer *tk)
{
	if (tk->tk_content)
		free(tk->tk_content);
	free(tk);
}
