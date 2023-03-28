/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:02:44 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/28 21:42:12 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR -1
// # define ERROR_P NULL

extern int	g_exit_status;

#include "../library/libft/libft.h"
// #include "../library/get_next_line/get_next_line.h"

// #include <string.h>
// #include <stdlib.h>

// typedef struct s_cmd {
// 	int		ac;
// 	char	**av;
// 	char	*rd_in; // <
// 	char	*rd_out; // >
// 	char	*rd_heredoc; // <<
// 	char	*rd_append; // >>
// }	t_cmd;

# define R_FD 0
# define W_FD 1

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
	// t_list	*rd_in; // <
	// t_list	*rd_out; // >
	// t_list	*rd_heredoc; // <<
	// t_list	*rd_append; // >>
}	t_cmd;

# include "../headers/mini_utils.h"
# include "../headers/mini_env.h"
# include "../headers/mini_parsing.h"
# include "../headers/mini_exe.h"



// signal
void	init_rl_catch_signals(void);
void	sigint_handler(int sig);
void	setting_signal(void);
void	setting_signal_exe(void);


#endif
