/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:48:39 by heson             #+#    #+#             */
/*   Updated: 2023/03/22 17:51:49 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

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
		return (NULL);
	i = 0;
	strp = (char *)str;
	while (strp && *strp && i < size)
		ret[i++] = *strp++;
	ret[i] = '\0';
	return (ret);
}

int	perror_n_return(char *err_msg)
{
	printf("%s\n", err_msg);
	return (-1);
}