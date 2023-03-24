/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:11:11 by heson             #+#    #+#             */
/*   Updated: 2023/03/24 19:57:43 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "built_in.h"

int	ft_echo(t_cmd *cmd)
{
	int		option_n;
	int		val_idx;
	char	*val;

	option_n = 1;
	val_idx = 1;
	if (cmd->ac >= 2)
	{
		if (cmd->av[1] && ft_strncmp(cmd->av[1], "-n", 10) == 0)
		{
			option_n = 0;
			val_idx++;
		}
	}
	while (val_idx < cmd->ac)
		ft_putstr_fd(cmd->av[val_idx], STDOUT_FILENO);
	if (option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

// int main()
// {
//     ft_echo("hello", 1);
// }