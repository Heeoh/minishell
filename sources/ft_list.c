/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:25:39 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/15 21:46:41 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_cmd	*ft_listnew(int content)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->ac = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_listadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_listadd_back(t_list **lst, t_list *new)
{
	t_list	*pre;

	pre = ft_lstlast(*lst);
	if (!pre)
	{
		*lst = new;
		return ;
	}
	pre->next = new;
	return ;
}

void	ft_listclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*p;

	p = *lst;
	while (p)
	{
		next = p->next;
		ft_lstdelone(p, del);
		p = next;
	}
	*lst = NULL;
}

void	ft_listdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}

t_list	*ft_listlast(t_list *lst)
{
	t_list	*p;

	p = lst;
	if (!p)
		return (NULL);
	while (p->next)
		p = p->next;
	return (p);
}