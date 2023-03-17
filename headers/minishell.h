/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:02:44 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/17 21:53:18 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE_N 2
# define ERROR -1
// # define ERROR_P NULL

#include "../library/libft/libft.h"
#include "../library/get_next_line/get_next_line.h"
#include "../headers/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include "../headers/mini_env.h"

typedef struct s_cmd {
	int		ac;
	char	**av;
	char	*rd_in; // <
	char	*rd_out; // >
	char	*rd_heredoc; // <<
	char	*rd_append; // >>
}	t_cmd;


int		parsing(char *line, t_list **cmds, t_list *env_lst);
int		is_quote(char q, int quote);
int		init_cmd_av(t_list *tk_lst, char **av[], int ac);
t_list	*init_cmd_val(t_list *tk_lst, t_cmd **cmd);
int	init_cmd_lst(t_list **cmd, t_list *tk_lst);

#endif
