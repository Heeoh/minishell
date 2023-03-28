/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:42:20 by heson             #+#    #+#             */
/*   Updated: 2023/03/28 20:37:22 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/mini_env.h"

int	is_var_char(char ch)
{
	if (!ft_isalnum(ch) && ch != '_')
		return (0);
	return (1);
}

int	is_valid_key(char *key)
{
	char	*p;

	p = key;
	if (ft_isdigit(*p))
		return (0);
	else if (is_var_char(*p))
	{
		while (++p && *p)
		{
			if (!is_var_char(*p))
				return (0);
		}
		return (1);
	}
	return (0);
}

char	*ft_getenv(t_list *env_lst, char *key)
{
	t_list	*p;

	p = env_lst;
	while (p)
	{
		if (ft_strncmp(key, ((t_env_var *)p->content)->key, 1000) == 0)
			return (((t_env_var *)p->content)->value);
		p = p->next;
	}
	return (NULL);
}

int	ft_putenv(t_list *env_lst, char *arg)
{
	t_env_var	*new_env;
	t_list		*new_node;
	t_list		*p;

	new_env = create_env_var(arg);
	if (!(new_env && is_valid_key(new_env->key)))
		return (-1);
	if (ft_strncmp(new_env->key, "_", 10) == 0)
		return (0);
	p = env_lst;
	while (p)
	{
		if (ft_strncmp(new_env->key, ((t_env_var *)p->content)->key, 1000) == 0)
		{
			if (((t_env_var *)p->content)->value)
				ft_free_str(&((t_env_var *)p->content)->value);
			((t_env_var *)p->content)->value = new_env->value;
			((t_env_var *)p->content)->is_tmp = 0;
			return (0);
		}
		if (!p->next->next)
			break ;
		p = p->next;
	}
	new_node = ft_lstnew(new_env);
	ft_lstadd_front(&(p->next), new_node);
	p->next = new_node;
	return (0);
}

int	get_env_key(char *sp, char **env_key)
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
		return (-1);
	ft_strlcpy(*env_key, sp + 1, key_len + 1);
	return (key_len);
}

char	*replace_env(t_list *env_lst, char *data)
{
	char		*dollar_pos;
	int			env_sp;
	int			env_ep;
	char		*front;
	char		*back;
	t_env_var	target_env;
	extern int	g_exit_status;
	char		*tmp;

	tmp = 0;
	while (data)
	{
		dollar_pos = ft_strchr(data, '$');
		if (!dollar_pos)
			return (data);
		env_sp = dollar_pos - data;
		env_ep = env_sp + get_env_key(data + env_sp, &(target_env.key));
		if (env_sp == env_ep)
			return (data);
		if (env_sp > env_ep)
			return (NULL);
		front = ft_strndup(data, env_sp);
		back = ft_strndup(data + env_ep + 1, ft_strlen(data) - env_ep);
		if (ft_strncmp(target_env.key, "?", 5) == 0)
		{
			tmp = ft_itoa(g_exit_status);
			target_env.value = tmp;	
		}
		else
			target_env.value = ft_getenv(env_lst, target_env.key);
		free(data);
		data = strjoin_n_free(ft_strjoin(front, target_env.value), back);
		if (front)
			free(front);
		if (tmp)
			free(tmp);
	}
	return (NULL);
}

/*
int main(int ac, char *av[], char *env[]){

	t_list	*mini_env;
	char	**env_arr;
	// t_list	*sorted;

	mini_env = init_env_lst(env);
	env_arr = envlst_2_arr(mini_env);
	for (char **p = env_arr; p && *p; p++) {
		printf("%s\n", *p);
	}
	ft_putenv(mini_env, "1=kkkk");
	// sorted = ft_lstmap(mini_env, copy_env_var, free_env_var);
	// sort_env_lst(&sorted);
	// print_env_lst(sorted, 1);
	// print_env_lst(mini_env);
	// printf("%s\n", getenv("water"));
	// ft_export("water=삼다수");
	// printf("%s\n", getenv("water"));
}
*/
