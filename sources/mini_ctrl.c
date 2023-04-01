/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:56:12 by jkim3             #+#    #+#             */
/*   Updated: 2023/04/01 19:10:07 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	sigint_handler(int sig)
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

void	setting_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
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
