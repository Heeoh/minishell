/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:42:45 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:49:36 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_env.h"

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
