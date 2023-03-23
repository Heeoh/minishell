/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:37:44 by heson             #+#    #+#             */
/*   Updated: 2023/03/24 02:32:03 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/mini_env.h"

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
	key = (char *)malloc(key_len + 1);
	val = (char *)malloc(val_len + 1);
	ft_strlcpy(key, arg, key_len + 1);
	*val = '\0';
	if (eq_pos)
		ft_strlcpy(val, eq_pos + 1, val_len + 1);
	return (create_env_var_struct(key, val, !eq_pos));
}

t_env_var	*create_env_var_struct(char *key, char *val, char is_my_tmp)
{
	t_env_var	*ret;

	ret = (t_env_var *)malloc(sizeof(t_env_var));
	if (!ret)
		return (NULL);
	ret->is_tmp = is_my_tmp;
	ret->key = key;
	ret->value = val;
	return (ret);
}

void	free_env_var(void	*arg)
{
	t_env_var	*env_var;

	env_var = arg;
	if (env_var->key)
		free(env_var->key);
	if (env_var->value)
		free(env_var->value);
	free(env_var);
}

void	*copy_env_var(void *arg)
{
	t_env_var	*var;

	var = arg;
	return (create_env_var_struct(var->key, var->value, var->is_tmp));
}