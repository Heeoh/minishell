/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:36:09 by heson             #+#    #+#             */
/*   Updated: 2023/03/21 19:48:31 by heson            ###   ########.fr       */
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

char	*get_token(t_list *env_lst, t_tokenizer *tokenizer)
{
	char	*tmp;
	char	*new_token;
	char	*sp;
	char	*ep;

	sp = tokenizer->sp;
	ep = tokenizer->line;
	new_token = NULL;
	tmp = ft_strndup(sp, ep - sp);
	if (ft_strchr(tmp, '$') && tokenizer->quote != 1)
		tmp = replace_env(env_lst, tmp);
	new_token = strjoin_n_free(tokenizer->tk_content, tmp);
	return (new_token);
}

int	tokenizing_quote(t_list *env_lst, t_tokenizer **tokenizer)
{
	t_tokenizer	*tk_p;

	tk_p = *tokenizer;
	tk_p->tk_content = get_token(env_lst, tk_p);
	tk_p->line++;
	tk_p->sp = tk_p->line;
	while (is_quote(*tk_p->line, tk_p->quote))
	{
		if (!tk_p->line)
		{
			printf("quote error : not closed quote\n");
			return (ERROR);
		}
		tk_p->line++;
	}
	tk_p->tk_content = get_token(env_lst, tk_p);
	tk_p->tk_size = ft_strlen(tk_p->tk_content);
	tk_p->line++;
	tk_p->sp = tk_p->line;
	tk_p->quote = 0;
	*tokenizer = tk_p;
	return (0);
}

int	is_token_separator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>' || c == '\0')
		return (1);
	return (0);
}

int	perror_n_return(char *err_msg)
{
	printf("%s\n", err_msg);
	return (-1);
}

t_tokenizer	*init_tokenizer(char *line)
{
	t_tokenizer	*tokenizer;

	tokenizer = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	tokenizer->line = line;
	tokenizer->sp = line;
	tokenizer->quote = 0;
	tokenizer->tk_content = NULL;
	tokenizer->tk_size = 0;
	return (tokenizer);
}

void	push_token_back(t_list *env_lst, t_list **tk_lst,
							t_tokenizer *tokenizer)
{
	char	*ep;

	ep = tokenizer->line;
	if (tokenizer->tk_size || tokenizer->sp < ep)
	{
		tokenizer->tk_content = get_token(env_lst, tokenizer);
		ft_lstadd_back(tk_lst, ft_lstnew(tokenizer->tk_content));
	}
	if (!*ep)
		return ;
	tokenizer->tk_size = 1;
	if (*ep != ' ')
	{
		if ((*ep == '<' || *ep == '>') && *ep == *(ep + 1))
			tokenizer->tk_size++;
		tokenizer->tk_content = ft_strndup(ep, tokenizer->tk_size);
		ft_lstadd_back(tk_lst, ft_lstnew(tokenizer->tk_content));
	}
	tokenizer->line = ep + tokenizer->tk_size;
	tokenizer->sp = tokenizer->line;
	tokenizer->tk_content = NULL;
	tokenizer->tk_size = 0;
}

int	tokenizing(t_list **tk_lst, char *line, t_list *env_lst)
{
	t_tokenizer	*tokenizer;

	tokenizer = init_tokenizer(line);
	while (1)
	{
		tokenizer->quote = is_quote(*tokenizer->line, tokenizer->quote);
		if (tokenizer->quote == 0)
		{
			if (*tokenizer->line == ';' || *tokenizer->line == '\\')
				return (perror_n_return("not a valid character"));
			if (is_token_separator(*tokenizer->line))
			{
				push_token_back(env_lst, tk_lst, tokenizer);
				if (!*tokenizer->line)
					break ;
			}
			else
				tokenizer->line++;
		}
		else if (tokenizing_quote(env_lst, &tokenizer) == ERROR)
			return (ERROR);
	}
	free(tokenizer);
	return (0);
}
