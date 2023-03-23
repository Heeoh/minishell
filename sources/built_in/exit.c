/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:46:05 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/23 15:03:43 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int is_num(char *str)
{
	int	i;

	i = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	exit_argm(char *argm)
{
	printf("exit\n");
	printf("miniHell: exit: %s:  numeric argument required\n", argm);
	exit(255);
}

int	ft_exit(t_list *p)
{
	if (!ft_strncmp("exit", p->content, 1000) && !p->next)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strncmp("exit", p->content, 1000) && p->next)
	{
		if  (is_num(p->next->content))
			exit_argm(p->next->content);
		else if (p->next->next)
		{
			printf("miniHell: too many arguments\n");
			return (EXIT_FAILURE);
		}
	}
	printf("exit\n");
	exit(ft_atoi(p->next->content));
}
