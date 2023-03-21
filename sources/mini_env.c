/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:42:20 by heson             #+#    #+#             */
/*   Updated: 2023/03/21 22:22:59 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

void	*copy_env_var(void *arg)
{
	t_env_var	*var;

	var = arg;
	return (create_env_var_struct(var->key, var->value, var->is_tmp));
}

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
	char		*val;

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
			break ;
		}
		if (!p->next->next)
			break ;
		p = p->next;
	}
	printf("%s\n", ((t_env_var *)p->content)->key);
	new_node =  ft_lstnew(new_env);
	ft_lstadd_front(&(p->next), new_node);
	p->next = new_node;
}

void	split_lst(t_list *source, t_list **front, t_list **back)
{
	t_list	*fast;
	t_list	*slow;

	if (source == NULL || source->next == NULL)
	{
		*front = source;
		*back = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = source;
		*back = slow->next;
		slow->next = NULL;
	}
}

t_list	*merge(t_list *a, t_list *b)
{
	t_list		*ret;
	int			cmp;
	t_env_var	*a_var;
	t_env_var	*b_var;

	ret = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	a_var = (t_env_var *)a->content;
	b_var = (t_env_var *)b->content;
	cmp = ft_strncmp(a_var->key, b_var->key, 1000);
	if (cmp <= 0)
	{
		ret = a;
		ret->next = merge(a->next, b);
	}
	else
	{
		ret = b;
		ret->next = merge(a, b->next);
	}
	return (ret);
}

void	sort_env_lst(t_list **env_lst)
{
	t_list	*lst;
	t_list	*a;
	t_list	*b;

	lst = *env_lst;
	if (lst == NULL || lst->next == NULL)
		return ;
	split_lst(lst, &a, &b);
	sort_env_lst(&a);
	sort_env_lst(&b);
	*env_lst = merge(a, b);
}

void	print_env_lst(t_list *env_lst, int env_flag)
{
	t_list		*p;
	t_env_var	*var;

	p = env_lst;
	while (p)
	{
		var = (t_env_var *)p->content;
		if (env_flag)
		{
			if (!var->is_tmp)
				printf("%s=%s\n", var->key, var->value);
		}
		else
		{
			if (var->is_tmp)
				printf("declare -x %s\n", var->key);
			else if (ft_strncmp(var->key, "_", 5) != 0)
				printf("declare -x %s=\"%s\"\n", var->key, var->value);
			
		}
		p = p->next;
	}
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

t_list	*init_env(char *org_env[])
{
	t_list	*mini_env;
	t_list	*new_env_node;

	mini_env = NULL;
	while (org_env && *org_env)
	{
		new_env_node = ft_lstnew((void *)create_env_var(*org_env++));
		ft_lstadd_back(&mini_env, new_env_node);
	}
	return (mini_env);
}

// int main(int ac, char *av[], char *env[]){

// 	t_list	*mini_env;
// 	t_list	*sorted;

// 	mini_env = init_env(env);
// 	ft_putenv(mini_env, "kkk=kkkk");
// 	sorted = ft_lstmap(mini_env, copy_env_var, free_env_var);
// 	sort_env_lst(&sorted);
// 	print_env_lst(sorted, 1);
// 	// print_env_lst(mini_env);
// 	// printf("%s\n", getenv("water"));
// 	// ft_export("water=삼다수");
// 	// printf("%s\n", getenv("water"));
// }
