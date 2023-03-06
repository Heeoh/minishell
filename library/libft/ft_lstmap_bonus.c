/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:30:22 by heson             #+#    #+#             */
/*   Updated: 2022/07/22 18:09:55 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*p;
	t_list	*new_p;

	new_list = NULL;
	p = lst;
	while (p)
	{
		new_node = ft_lstnew("");
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_node->content = f(p->content);
		if (!new_list)
			new_list = new_node;
		else
			new_p->next = new_node;
		new_p = new_node;
		p = p->next;
	}
	return (new_list);
}
