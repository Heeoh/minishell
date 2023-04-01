/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:12:54 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:40:08 by jkim3            ###   ########.fr       */
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
