/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:11:24 by heson             #+#    #+#             */
/*   Updated: 2023/03/24 02:48:12 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

void	init_rl_catch_signals(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
}

void    sigint_handler(int sig) {
	if (sig != SIGINT)
		exit(0);
	ft_putstr_fd("\n", STDOUT_FILENO);	
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void    setting_signal(void)
{
    signal(SIGINT, sigint_handler);	// CTRL + C
    signal(SIGQUIT, SIG_IGN);		// CTRL + /
}
