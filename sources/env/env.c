/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:42:20 by heson             #+#    #+#             */
/*   Updated: 2023/04/02 05:00:44 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_env.h"
#include "mini_utils.h"

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
		return (free_env_n_return(new_env, -1));
	if (ft_strncmp(new_env->key, "_", 10) == 0)
		return (free_env_n_return(new_env, 0));
	p = env_lst;
	while (p)
	{
		if (compare_strs(new_env->key, ((t_env_var *)p->content)->key) == 0)
		{
			if (ft_strncmp(new_env->value, "", 10) == 0)
				return (free_env_n_return(new_env, 0));
			free_env_var(p->content);
			p->content = new_env;
			return (0);
		}
		p = p->next;
	}
	cus_ft_lstadd_back(&env_lst, new_env);
	return (0);
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
