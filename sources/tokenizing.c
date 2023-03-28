/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:36:09 by heson             #+#    #+#             */
/*   Updated: 2023/03/28 21:22:23 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/mini_parsing.h"

int	tokenizing(t_list **tk_lst, char *line, t_list *env_lst)
{
	t_tokenizer	*tokenizer;

	tokenizer = init_tokenizer(line);
	// tokenizer malloc error
	while (1)
	{
		tokenizer->quote = is_quote(*tokenizer->line, tokenizer->quote);
		if (tokenizer->quote == 0)
		{
			if (*tokenizer->line == ';' || *tokenizer->line == '\\') // 이거 그냥 문자 처리..?
				return (perror_n_return("syntax error : invlaid character", 1, 258));
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
	if (tokenizer)
		free(tokenizer);
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

int	tokenizing_quote(t_list *env_lst, t_tokenizer **tokenizer)
{
	t_tokenizer	*tk_p;

	tk_p = *tokenizer;
	tk_p->tk_content = get_token(env_lst, tk_p, 0);
	//null
	tk_p->line++;
	tk_p->sp = tk_p->line;
	while (is_quote(*tk_p->line, tk_p->quote))
	{
		if (!tk_p->line)
			return (perror_n_return("syntax error : not closed quote", 1, 258));
		tk_p->line++;
	}
	tk_p->tk_content = get_token(env_lst, tk_p, tk_p->quote);
	//null
	tk_p->tk_size = ft_strlen(tk_p->tk_content);
	tk_p->line++;
	tk_p->sp = tk_p->line;
	tk_p->quote = 0;
	*tokenizer = tk_p;
	return (0);
}

void	push_token_back(t_list *env_lst, t_list **tk_lst,
							t_tokenizer *tokenizer)
{
	char	*ep;

	ep = tokenizer->line;
	if (tokenizer->tk_size || tokenizer->sp < ep)
	{
		tokenizer->tk_content = get_token(env_lst, tokenizer, 0);
		//null
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

char	*get_token(t_list *env_lst, t_tokenizer *tokenizer, int in_quote)
{
	char	*tmp;
	char	*new_token;
	char	*sp;
	char	*ep;
	char	*dollar_pos;

	sp = tokenizer->sp;
	ep = tokenizer->line;
	new_token = NULL;
	dollar_pos = 0;
	tmp = ft_strndup(sp, ep - sp);
	if (!tmp)
		return (NULL);
	dollar_pos = ft_strchr(tmp, '$');
	if (dollar_pos && !*(dollar_pos + 1) && tokenizer->quote && !in_quote)
	{
		tmp[ft_strlen(tmp) - 1] = '\0';
	}
	else if (dollar_pos && in_quote != 1)
		tmp = replace_env(env_lst, tmp);
	if (!tmp)
		return (NULL);
	new_token = strjoin_n_free(tokenizer->tk_content, tmp);
	return (new_token);
}
