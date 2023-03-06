/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_man.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:11:47 by heson             #+#    #+#             */
/*   Updated: 2022/07/27 16:20:08 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_word_cnt(const char *str, char c)
{
	const char		*p;
	unsigned int	cnt;

	cnt = 0;
	p = str;
	if (*p && !c)
		return (1);
	while (*p)
	{
		if (*p == c)
			p++;
		if (*p && *p != c)
		{
			cnt++;
			p++;
			while (*p && *p != c)
				p++;
		}
	}
	return (cnt);
}

char	*create_word(const char *str, char c, char **res)
{
	const char		*word_sp;

	word_sp = str++;
	while (*str && *str != c)
		str++;
	*res = (char *)malloc(str - word_sp + 1);
	if (!*res)
		return (NULL);
	ft_strlcpy(*res, word_sp, str - word_sp + 1);
	return ((char *)str);
}

void	free_all(char **res, unsigned int i)
{
	char	**p;

	p = res;
	while (p < res + i)
		free(*p++);
	free (res);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	word_cnt;
	unsigned int	i;
	char			**res;

	if (!s)
		return (NULL);
	word_cnt = get_word_cnt(s, c);
	res = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s && i < word_cnt)
	{
		if (*s != c)
			s = create_word(s, c, &res[i++]);
		if (!s)
		{
			free_all(res, i);
			return (NULL);
		}
		if (*s)
			s++;
	}
	res[i] = 0;
	return (res);
}
