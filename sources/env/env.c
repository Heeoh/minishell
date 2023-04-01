/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:42:20 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 19:57:19 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_env.h"
#include "mini_utils.h"

extern int	g_exit_status;

char	*ft_getenv(t_list *env_lst, char *key)
{
	t_list	*p;

	p = env_lst;
	while (p)
	{
		if (compare_strs(key, ((t_env_var *)p->content)->key) == 0)
			return (((t_env_var *)p->content)->value);
		p = p->next;
	}
	return (NULL);
}

int	ft_putenv(t_list *env_lst, char *arg)
{
	t_env_var	*new_env;
	t_list		*p;

	new_env = create_env_var(arg);
	if (!(new_env && is_valid_key(new_env->key)))
		return (-1);
	if (ft_strncmp(new_env->key, "_", 10) == 0)
		return (0);
	p = env_lst;
	while (p)
	{
		if (compare_strs(new_env->key, ((t_env_var *)p->content)->key) == 0)
		{
			if (ft_strncmp(new_env->value, "", 10) == 0)
			{
				free_env_var(new_env);
				return (0);
			}
			free_env_var(p->content);
			p->content = new_env;
			return (0);
		}
		p = p->next;
	}
	cus_ft_lstadd_back(&env_lst, new_env);
	return (0);
}

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
	*env_key = (char *)malloc(sizeof(char *) * (key_len + 1));
	if (!*env_key)
		exit(1);
	ft_strlcpy(*env_key, sp + 1, key_len + 1);
	return (key_len);
}

static char	*split_by_dollar(char *data, char **front, char **back,
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
	if (ft_strncmp(key, "?", 5) == 0)
		return (ft_itoa(g_exit_status));
	env_val = ft_getenv(env_lst, key);
	if (env_val)
		return (ft_strdup(env_val));
	return (ft_strndup("", 0));
}

char	*replace_env(t_list *env_lst, char *data)
{
	char		*front;
	char		*back;
	char		*env_val;

	front = 0;
	back = 0;
	env_val = 0;
	while (data)
	{
		env_val = split_by_dollar(data, &front, &back, env_lst);
		if (!env_val)
			return (NULL);
		if (compare_strs(env_val, data) == 0)
			return (data);
		free(data);
		data = strjoin_n_free(strjoin_n_free(front, env_val), back);
	}
	return (NULL);
}
