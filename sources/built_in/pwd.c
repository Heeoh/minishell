/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:58:15 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:38:46 by jkim3            ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}
