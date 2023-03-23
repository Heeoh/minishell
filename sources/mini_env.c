/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:42:20 by heson             #+#    #+#             */
/*   Updated: 2023/03/23 14:42:03 by heson            ###   ########.fr       */
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
	if (is_var_char(*p) && !ft_isdigit(*p))
	{
		while (++p && *p)
		{
			if (!is_var_char(*p))
				return (0);
		}
	}
	return (1);
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

void	ft_putenv(t_list *env_lst, char *arg)
{
	t_env_var	*new_env;
	t_list		*new_node;
	t_list		*p;

	new_env = create_env_var(arg);
	if (!new_env)
		return ;
	if (!is_valid_key(new_env->key))
		return ;
	p = env_lst;
	while (p)
	{
		if (ft_strncmp(new_env->key, ((t_env_var *)p->content)->key, 1000) == 0)
		{
			if (((t_env_var *)p->content)->value)
				ft_free_str(&((t_env_var *)p->content)->value);
			((t_env_var *)p->content)->value = new_env->value;
			((t_env_var *)p->content)->is_tmp = 0;
			return ;
		}
		if (!p->next->next)
			break ;
		p = p->next;
	}
	new_node =  ft_lstnew(new_env);
	ft_lstadd_front(&(p->next), new_node);
	p->next = new_node;
}


int	get_env_key(char *sp, char	**env_key)
{
	char	*ep;
	int		key_len;

	ep = sp + 1;
	if (!*ep)
	{
		*env_key = (char *)malloc(sizeof(char));
		**env_key = '\0';
		return (0);
	}
	if (is_var_char(*ep) && !ft_isdigit(*ep))
	{
		while (++ep)
		{
			if (!is_var_char(*ep))
				break ;
		}
		ep--;
	}
	key_len = ep - sp;
	*env_key = (char *)malloc(sizeof(char *) * (key_len + 1));
	// null
	ft_strlcpy(*env_key, sp + 1, key_len + 1);
	return (key_len);
}

char	*replace_env(t_list *env_lst, char *data)
{
	int			env_sp;
	int			env_ep;
	char		*front;
	char		*back;
	t_env_var	target_env;

	env_sp = ft_strchr(data, '$') - data;
	env_ep = env_sp + get_env_key(data + env_sp, &(target_env.key));
	front = ft_strndup(data, env_sp);
	back = ft_strndup(data + env_ep + 1, ft_strlen(data) - env_ep);
	target_env.value = ft_strdup(ft_getenv(env_lst, target_env.key));
	return (strjoin_n_free(strjoin_n_free(front, target_env.value), back));
	// return (new_data);
}



// int main(int ac, char *av[], char *env[]){

// 	t_list	*mini_env;
// 	char	**env_arr;
// 	// t_list	*sorted;

// 	mini_env = init_env(env);
// 	env_arr = envlst_2_arr(mini_env);
// 	for (char **p = env_arr; p && *p; p++) {
// 		printf("%s\n", *p);
// 	}
// 	// ft_putenv(mini_env, "kkk=kkkk");
// 	// sorted = ft_lstmap(mini_env, copy_env_var, free_env_var);
// 	// sort_env_lst(&sorted);
// 	// print_env_lst(sorted, 1);
// 	// print_env_lst(mini_env);
// 	// printf("%s\n", getenv("water"));
// 	// ft_export("water=삼다수");
// 	// printf("%s\n", getenv("water"));
// }
