/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:42:20 by heson             #+#    #+#             */
/*   Updated: 2023/03/17 21:17:11 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/mini_env.h"

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

// ft_putenv

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

void	print_env_lst(t_list *env_lst)
{
	t_list		*p;
	t_env_var	*var;

	p = env_lst;
	while (p)
	{
		var = (t_env_var *)p->content;
		printf("%s=%s\n", var->key, var->value);
		p = p->next;
	}
}

int	is_var_char(char ch)
{
	if (!ft_isalnum(ch) && ch != '_')
		return (0);
	return (1);
}

char	*replace_env(t_list *env_lst, char *data)
{
	int	env_sp;
	int	env_ep;
	char	*env_key;
	char	*env_val;
	int		new_data_len;
	char	*new_data;
	int		env_val_len;

	env_sp = ft_strchr(data, '$') - data;
	env_ep = env_sp + 1;
	if (is_var_char(data[env_ep]) && !ft_isdigit(data[env_ep]))
	{
		while (++env_ep)
		{
			if (!is_var_char(data[env_ep]))
				break ;
		}
	}
	env_key = (char *)malloc(sizeof(char *) * (env_ep - env_sp));
	// null
	ft_strlcpy(env_key, &data[env_sp + 1], env_ep - env_sp);
	env_val = ft_getenv(env_lst, env_key);
	if (!env_val)
		env_val_len = 0;
	else
		env_val_len = ft_strlen(env_val);
	new_data_len = ft_strlen(data) - (env_ep - env_sp - 1) + env_val_len;
	new_data = (char *)malloc(sizeof(char) * new_data_len + 1);
	// null
	ft_strlcpy(new_data, data, env_sp + 1);
	if (env_val)
		ft_strlcpy(new_data + env_sp, env_val, env_val_len + 1);
	ft_strlcpy(new_data + env_sp + env_val_len, data + env_ep, ft_strlen(data) - env_ep + 1);
	free(env_key);
	// free(data);
	return (new_data);
}

t_list	*init_env(char *org_env[])
{
	t_list	*mini_env;

	mini_env = NULL;
	while (org_env && *org_env)
		ft_lstadd_back(&mini_env, ft_lstnew((void *)create_env_var(*org_env++)));
	return (mini_env);
}

// int main(int ac, char *av[], char *env[]){

// 	t_list	*mini_env;
// 	t_list	*sorted;

// 	mini_env = init_env(env);
// 	printf("%s\n", replace_env(mini_env, "'$path'"));
// 	// print_env_lst(mini_env);
	
// 	// printf("%s\n", getenv("water"));
// 	// ft_export("water=삼다수");
// 	// printf("%s\n", getenv("water"));
// }
