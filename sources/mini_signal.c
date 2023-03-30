/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:11:24 by heson             #+#    #+#             */
/*   Updated: 2023/03/30 17:36:01 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <termios.h>

void    sigint_handler(int sig)
{
	extern int	g_exit_status;

	if (sig != SIGINT)
		exit(0);
	g_exit_status = 1;	
	ft_putstr_fd("\n", STDOUT_FILENO);	
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void    setting_signal(void)
{
    signal(SIGINT, sigint_handler);	// CTRL + C
    signal(SIGQUIT, SIG_IGN);		// CTRL + /
}

void	set_termios(int echoctl_on)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &new_term);
	if (echoctl_on)
		new_term.c_lflag |= ECHOCTL; 
	if (!echoctl_on)
		new_term.c_lflag &= ~(ECHOCTL); 
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

void	set_ctrl(int termios_flag, void (*sigint)(int), void (*sigquit)(int))
{
	set_termios(termios_flag);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}
