/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exe.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:01:23 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:52:01 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXE_H
# define MINI_EXE_H

# include "minishell.h"
# include "../library/get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define PIPE_N 2
# define STD 2

void	execute(int cmd_cnt, t_list *cmd_p, t_list *env);

// cmd
int		find_cmd_path(char *cmd, t_list *env, char **path);
int		is_built_in(char *cmd);

// exe_utils
void	ft_free_2d_arr(char **arr);
void	set_exit_status(int status);
void	set_child_exe(int fd_std[], int heredoc_fd);
void	close_fds(int fds[][2]);

// redirection
int		do_redirection(int type, char *val, int *fd);
int		do_redirection_in(char *val, int *fd, char is_heredoc);
int		do_redirection_out(char *filename, int *fd, char is_append);
int		check_n_do_heredoc(t_list *rd_p, int fd_std[], int *fd);
int		do_heredoc(char *limiter, int *input_fd, int fd_std[]);

// rd_utils
int		get_heredoc_input(int fd[], int fd_std[], char *limiter);
int		wait_heredoc_input(int fd[], pid_t child_pid);

// pipe
int		child_process(int cmd_i, int cmd_cnt, int pipes[][2], int is_heredoc);
void	parent_process(int cmd_i, int pipes[][2]);
int		wait_processes(int child_cnt, pid_t last_pid, pid_t wait_pid);

#endif
