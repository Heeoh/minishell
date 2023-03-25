/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:51:19 by heson             #+#    #+#             */
/*   Updated: 2023/03/25 15:45:51 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_unset(char *key, t_list **env_lst)
{
	t_list	*p;
	t_list	*tmp;

	p = *env_lst;
	if (ft_strncmp(key, ((t_env_var *)(*env_lst)->content)->key, 1000) == 0)
	{
		tmp = p;
		*env_lst = p->next;
		ft_lstdelone(tmp, free_env_var);
		return (0);
	}
	while (p && p->next)
	{
		if (ft_strncmp(key, ((t_env_var *)p->next->content)->key, 1000) == 0)
		{
			tmp = p->next;
			p->next = p->next->next;
			ft_lstdelone(tmp, free_env_var);
		}
		p = p->next;
	}
}