/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:02:44 by jkim3             #+#    #+#             */
/*   Updated: 2023/04/01 19:24:29 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR -1
# define R_FD 0
# define W_FD 1

# include "../library/libft/libft.h"
# include "../headers/mini_utils.h"
# include "../headers/mini_env.h"
# include "../headers/mini_exe.h"
# include "mini_utils.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_exit_status;

enum e_rd_type {
	RD_IN = 0,
	RD_OUT,
	RD_HEREDOC,
	RD_APPEND,
	RD_CNT
};

typedef struct s_redirection {
	int		type;
	char	*val;
}	t_redirection;

typedef struct s_cmd {
	int		ac;
	char	**av;
	t_list	*rd;
}	t_cmd;

// signal
void	sigint_handler(int sig);
void	setting_signal(void);
void	set_termios(int echoctl_on);
void	set_ctrl(int termios_flag, void (*sigint)(int), void (*sigquit)(int));

#endif
