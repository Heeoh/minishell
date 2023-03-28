/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:24:20 by heson             #+#    #+#             */
/*   Updated: 2023/03/28 16:56:35 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_env(t_list *env)
{
	print_env_lst(env, 1);
	return (EXIT_SUCCESS);
}

// int main(int ac, char *av[], char *env[])
// {
//     ac = 0;
//     av = 0;
//     ft_env(env);
// }