/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:58:15 by heson             #+#    #+#             */
/*   Updated: 2023/04/02 04:37:47 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	if (ret)
		ft_putendl_fd(ret, STDOUT_FILENO);
	else
		return (perror_n_return("pwd", 0, 0, EXIT_FAILURE));
	free(ret);
	return (EXIT_SUCCESS);
}
