/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:24:20 by heson             #+#    #+#             */
/*   Updated: 2023/03/13 21:30:32 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../library/libft/libft.h"

void	ft_env(char *env[])
{
	char	**p;

	p = env;
	while (p && *p)
	{
		ft_putendl_fd(*p, STDOUT_FILENO);
		p++;
	}
}

// int main(int ac, char *av[], char *env[])
// {
//     ac = 0;
//     av = 0;
//     ft_env(env);
// }