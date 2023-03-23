/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exe.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:01:23 by heson             #+#    #+#             */
/*   Updated: 2023/03/22 17:30:47 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXE_H
# define MINI_EXE_H

#include "../headers/minishell.h"
#include <unistd.h> // access
#include <stdio.h> // printf 
#include <fcntl.h> // open, write

int	execute(int cmd_cnt, t_list *cmd_p, t_list *env);

char	*find_path(char *cmd, t_list *env);
char	*create_heredoc_file(char *limiter);
int		do_redirection_in(char *val, int *fd, char is_heredoc);
int		do_redirection_out(char *filename, int *fd, char is_append);
#endif
