/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:02:44 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/23 01:15:13 by heson            ###   ########.fr       */
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

# include "../headers/mini_env.h"
# include "../headers/mini_parsing.h"
# include "../headers/mini_exe.h"

typedef struct s_cmd {
	int		ac;
	char	**av;
	char	*rd_in; // <
	char	*rd_out; // >
	char	*rd_heredoc; // <<
	char	*rd_append; // >>
}	t_cmd;


// parsing
int		parsing(char *line, t_list **cmds, t_list *env_lst);
int		init_cmd_lst(t_list **cmd, t_list *tk_lst);
int		set_cmd_val(t_list **tk_lst, t_cmd **cmd);
t_list	*set_cmd_av(t_list *tk_p, char **av[], int ac);
void	set_cmd_redirection(char *type, char *val, t_cmd **cmd);
t_cmd	*create_cmd_struct(void);
t_list	*set_cmd_av(t_list *tk_p, char **av[], int ac);

// utils
char	*ft_strndup(const char *str, size_t size);
char	*strjoin_n_free(char *s1, char *s2);
void	ft_free_str(char **arg);
int		perror_n_return(char *err_msg);


// parsing

// exe
// int	execute(int cmd_cnt, t_list *cmds, t_list *env);

//env
t_list	*init_env(char *org_env[]);

#endif
