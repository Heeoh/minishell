/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 04:59:06 by heson             #+#    #+#             */
/*   Updated: 2023/04/02 15:39:04 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_env.h"
#include "mini_utils.h"

extern int	g_exit_status;

static int	get_env_key(char *sp, char **env_key)
{
	char	*ep;
	int		key_len;

	ep = sp + 1;
	if (!*ep)
		return (0);
	if (ft_isdigit(*ep) || *ep == '?')
		ep++;
	else if (is_var_char(*ep))
	{
		while (++ep)
		{
			if (!is_var_char(*ep))
				break ;
		}
	}
	key_len = ep - sp - 1;
	if (!key_len)
		return (0);
	*env_key = (char *)malloc(sizeof(char *) * (key_len + 1));
	if (!*env_key)
		exit(1);
	ft_strlcpy(*env_key, sp + 1, key_len + 1);
	return (key_len);
}

static char	*get_env_val(char *key, t_list *env_lst)
{
	char	*env_val;

	env_val = 0;
	if (ft_strncmp(key, "?", 5) == 0)
		env_val = ft_itoa(g_exit_status);
	else
	{
		env_val = ft_getenv(env_lst, key);
		if (env_val)
			env_val = ft_strdup(ft_getenv(env_lst, key));
		else
			env_val = ft_strndup("", 0);
	}
	free(key);
	return (env_val);
}

char	*split_by_dollar(char *data, char **front, char **back,
								t_list *env_lst)
{
	char		*dollar_pos;
	int			env_sp;
	int			env_ep;
	char		*key;
	char		*env_val;

	dollar_pos = ft_strchr(data, '$');
	if (!dollar_pos)
		return (data);
	env_sp = dollar_pos - data;
	env_ep = env_sp + get_env_key(data + env_sp, &key);
	if (env_sp == env_ep)
		return (data);
	if (env_sp > env_ep)
		return (NULL);
	*front = ft_strndup(data, env_sp);
	*back = ft_strndup(data + env_ep + 1, ft_strlen(data) - env_ep);
	env_val = get_env_val(key, env_lst);
	return (env_val);
}
