/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:35:43 by heson             #+#    #+#             */
/*   Updated: 2023/03/30 14:44:26 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/mini_env.h"

t_list	*init_env_lst(char *org_env[])
{
	t_list	*mini_env;
	t_list	*new_env_node;

	mini_env = NULL;
	while (org_env && *org_env)
	{
		new_env_node = ft_lstnew((void *)create_env_var(*org_env++));
		ft_lstadd_back(&mini_env, new_env_node);
	}
	ft_putenv(mini_env, "OLDPWD");
	return (mini_env);
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

char	**envlst_2_arr(t_list *env_lst)
{
	char		**arr;
	t_list		*lst_p;
	char		**arr_p;
	t_env_var	*env_var;

	arr = (char **)malloc(sizeof(char *) * (ft_lstsize(env_lst) + 1));
	if (!arr)
		exit(1);
	lst_p = env_lst;
	arr_p = arr;
	while (lst_p)
	{
		env_var = (t_env_var *)lst_p->content;
		*arr_p = ft_strjoin(ft_strjoin(env_var->key, "="), env_var->value);
		arr_p++;
		lst_p = lst_p->next;
	}
	*arr_p = NULL;
	return (arr);
}
