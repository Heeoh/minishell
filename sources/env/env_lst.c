/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:35:43 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:45:09 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_env.h"

t_list	*init_env_lst(char *org_env[])
{
	t_list	*mini_env;
	t_list	*new_env_node;

	mini_env = NULL;
	while (org_env && *org_env)
	{
		new_env_node = ft_lstnew((void *)create_env_var(*org_env++));
		if (!new_env_node)
			exit(1);
		if (ft_strncmp(((t_env_var *)new_env_node->content)->key, "OLDPWD", 10) == 0)
		{
			ft_free_str(&((t_env_var *)new_env_node->content)->value);
			((t_env_var *)new_env_node->content)->value = ft_strndup("", 0);
			((t_env_var *)new_env_node->content)->is_tmp = 1;
		}
		ft_lstadd_back(&mini_env, new_env_node);
	}
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
		if (!*arr_p)
			exit(1);
		arr_p++;
		lst_p = lst_p->next;
	}
	*arr_p = NULL;
	return (arr);
}
