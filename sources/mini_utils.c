/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:48:39 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:53:21 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "built_in.h"

char	*strjoin_n_free(char *s1, char *s2)
{
	char	*ret;

	ret = NULL;
	if (!s1 && !s2)
		return (ret);
	if (s1 && s2)
	{
		ret = ft_strjoin(s1, s2);
		if (!ret)
			exit(1);
		ft_free_str(&s1);
		ft_free_str(&s2);
	}
	else if (!s1)
		ret = ft_strndup(s2, ft_strlen(s2));
	else if (!s2)
		ret = ft_strndup(s1, ft_strlen(s1));
	return (ret);
}

char	*ft_strndup(const char *str, size_t size)
{
	char			*ret;
	char			*strp;
	unsigned int	i;

	ret = (char *)malloc(size + 1);
	if (!ret)
		exit(1);
	i = 0;
	strp = (char *)str;
	while (strp && *strp && i < size)
		ret[i++] = *strp++;
	ret[i] = '\0';
	return (ret);
}

void	cus_ft_lstadd_back(t_list **lst, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		exit(1);
	ft_lstadd_back(lst, new);
}

int	compare_strs(char *str1, char *str2)
{
	int		len1;
	int		len2;
	int		cmp_len;

	len1 = 0;
	len2 = 0;
	if (str1)
		len1 = ft_strlen(str1);
	if (str2)
		len2 = ft_strlen(str2);
	cmp_len = len1;
	if (cmp_len < len2)
		cmp_len = len2;
	return (ft_strncmp(str1, str2, cmp_len + 10));
}

int	per_n_ret(char *pos, char *msg1, char *msg2, int exit_status)
{
	extern int	g_exit_status;

	g_exit_status = exit_status;
	ft_putstr_fd("minishell: ", 2);
	if (pos)
	{
		ft_putstr_fd(pos, 2);
		write(2, ": ", 2);
	}
	if (msg1)
	{
		ft_putstr_fd(msg1, 2);
		write(2, ": ", 2);
	}
	if (msg2)
		ft_putendl_fd(msg2, 2);
	return (EXIT_FAILURE);
}
