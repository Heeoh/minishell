/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:48:39 by heson             #+#    #+#             */
/*   Updated: 2023/03/29 21:19:41 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "built_in.h"
#include <errno.h>

void	ft_free_str(char **arg)
{
	if (arg && *arg)
		free(*arg);
	*arg = NULL;
}

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
			return (NULL);
		ft_free_str(&s1);
		ft_free_str(&s2);
	}
	else if (!s1)
		ret = ft_strdup(s2);
	else if (!s2)
		ret = ft_strdup(s1);
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

int	perror_n_return(char *err_pos, char *err_msg, int is_custom, int exit_status)
{
	extern int	g_exit_status;

	g_exit_status = exit_status;
	ft_putstr_fd("minishell: ", 2);
	if (err_pos)
	{
		ft_putstr_fd(err_pos, 2);
		write(2, ": ", 2);
	}
	// if (is_custom)
	// 	printf("%s\n", err_msg);
	// else
	if (is_custom)
		ft_putendl_fd(err_msg, 2);
	else
		perror("");
	return (-1);
}

void	perror_n_exit(char *err_msg, int is_custom, int exit_status)
{
	perror_n_return(0, err_msg, is_custom, exit_status);
	exit(g_exit_status);
}
