/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:37:44 by heson             #+#    #+#             */
/*   Updated: 2023/03/30 17:49:08 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/mini_env.h"

t_env_var	*create_env_var(char *arg)
{
	char		*eq_pos;
	char		*key;
	char		*val;
	int			key_len;
	int			val_len;

	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
	{
		key_len = ft_strlen(arg);
		val_len = 0;
	}
	else
	{
		key_len = eq_pos - arg;
		val_len = ft_strlen(arg) - key_len - 1;
	}
	key = ft_strndup(arg, key_len);
	if (eq_pos)
		val = ft_strndup(eq_pos + 1, val_len);
	else
		val = ft_strndup("", 0);
	return (create_env_var_struct(key, val, !eq_pos));
}

t_env_var	*create_env_var_struct(char *key, char *val, int is_tmp)
{
	t_env_var	*ret;

	ret = (t_env_var *)malloc(sizeof(t_env_var));
	if (!ret)
		exit(1);
	ret->is_tmp = is_tmp;
	ret->key = key;
	ret->value = val;
	return (ret);
}

void	free_env_var(void	*arg)
{
	t_env_var	*env_var;

	env_var = (t_env_var *)arg;
	if (env_var->key)
		free(env_var->key);
	if (env_var->value)
		free(env_var->value);
	free(env_var);
}

void	*copy_env_var(void *arg)
{
	t_env_var	*var;
	char		*key;
	char		*value;
	t_env_var	*copied;

	var = (t_env_var *)arg;
	key = ft_strdup(var->key);
	if (!key)
		exit(1);
	value = ft_strdup(var->value);
	if (!value)
		exit(1);
	copied = create_env_var_struct(key, value, var->is_tmp); 
	return (copied);
}
