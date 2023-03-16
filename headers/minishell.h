/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:02:44 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/16 21:19:53 by jkim3            ###   ########.fr       */
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

typedef struct s_cmd {
	int		ac;
	char	**av;
	char	*rd_in; // <
	char	*rd_out; // >
	char	*rd_heredoc; // <<
	char	*rd_append; // >>
}	t_cmd;

typedef struct s_tk {
	int		is_env;
	char	*data;
}	t_tk;

int		parsing(char *line, t_cmd **cmd);
int		is_quote(char q, int quote);
char	*crt_pipe(t_cmd *cmd, char *line, int i, int j);
t_cmd	*ft_listnew(int content);
void	ft_listadd_front(t_list **lst, t_list *new);
void	ft_listadd_back(t_list **lst, t_list *new);
void	ft_listclear(t_list **lst, void (*del)(void*));
void	ft_listdelone(t_list *lst, void (*del)(void*));
t_list	*ft_listlast(t_list *lst);

#endif
