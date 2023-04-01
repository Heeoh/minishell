/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:26:11 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 19:49:16 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mini_exe.h"
#include "built_in.h"

static int	exe_built_in(t_cmd *cmd_p, t_list *env_lst, int cmd_type)
{
	if (cmd_type == BI_CD)
		return (ft_cd(cmd_p->av[1], env_lst));
	if (cmd_type == BI_ECHO)
		return (ft_echo(cmd_p));
	if (cmd_type == BI_ENV)
		return (ft_env(env_lst));
	if (cmd_type == BI_EXIT)
		return (ft_exit(cmd_p));
	if (cmd_type == BI_EXPORT)
		return (ft_export(cmd_p, env_lst));
	if (cmd_type == BI_PWD)
		return (ft_pwd());
	if (cmd_type == BI_UNSET)
		return (ft_unset(cmd_p, &env_lst));
	return (-1);
}

static int	exe_a_cmd(t_cmd *cmd, t_list *env, int heredoc_fd, int fd_std[])
{
	char			*path;
	t_list			*rd_p;
	int				is_builtin;
	int				fd;
	int				ret;

	is_builtin = is_built_in(cmd->av[0]);
	if (is_builtin < 0 && find_cmd_path(cmd->av[0], env, &path) < 0)
		return (ERROR);
	rd_p = cmd->rd;
	while (rd_p)
	{
		fd = -1;
		if (((t_redirection *)rd_p->content)->type == RD_HEREDOC)
			fd = heredoc_fd;
		if (do_redirection(((t_redirection *)rd_p->content)->type,
				((t_redirection *)rd_p->content)->val, &fd) < 0)
			return (ERROR);
		rd_p = rd_p->next;
	}
	set_child_exe(fd_std, heredoc_fd);
	if (!(cmd->av) || !*(cmd->av))
		return (0);
	if (is_builtin >= 0)
		ret = exe_built_in(cmd, env, is_builtin);
	else
		ret = execve(path, cmd->av, envlst_2_arr(env));
	if (ret < 0)
		free(path);
	return (ret);
}

static void	exe_n_exit(t_cmd *cmd, t_list *env, int heredoc_fd, int fd_std[])
{
	int	ret;

	ret = exe_a_cmd(cmd, env, heredoc_fd, fd_std);
	if (heredoc_fd > 0)
		close(heredoc_fd);
	if (ret < 0)
		exit(g_exit_status);
	exit(EXIT_SUCCESS);
}

static int	exe_multiple_cmds(int cmd_cnt, t_list *cmd_p,
								t_list *env, int fds[][2])
{
	int		cmd_i;
	pid_t	pid;
	int		heredoc_fd;

	cmd_i = -1;
	while (++cmd_i < cmd_cnt)
	{
		if (check_n_do_heredoc(((t_cmd *)cmd_p->content)->rd,
				fds[STD], &heredoc_fd) < 0)
			return (ERROR);
		if (pipe(fds[cmd_i % PIPE_N]) == -1)
			perror_n_exit("pipe", 0, EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			perror_n_exit("fork", 0, EXIT_FAILURE);
		else if (!pid)
		{
			child_process(cmd_i, cmd_cnt, fds, heredoc_fd >= 0);
			exe_n_exit(cmd_p->content, env, heredoc_fd, fds[STD]);
		}
		else if (pid)
			parent_process(cmd_i, fds);
		cmd_p = cmd_p->next;
	}
	return (wait_processes(cmd_cnt, pid, pid));
}

void	execute(int cmd_cnt, t_list *cmd_p, t_list *env)
{
	int	fds[PIPE_N + 1][2];
	int	heredoc_fd;

	signal(SIGINT, SIG_IGN);
	fds[0][R_FD] = -1;
	fds[0][W_FD] = -1;
	fds[1][R_FD] = -1;
	fds[1][W_FD] = -1;
	fds[STD][R_FD] = dup(STDIN_FILENO);
	fds[STD][W_FD] = dup(STDOUT_FILENO);
	if (cmd_cnt == 1 && is_built_in(((t_cmd *)cmd_p->content)->av[0]) >= 0)
	{
		if (check_n_do_heredoc(((t_cmd *)cmd_p->content)->rd,
				fds[STD], &heredoc_fd) < 0)
			return ;
		if (exe_a_cmd(cmd_p->content, env, heredoc_fd, fds[STD]) != ERROR)
			g_exit_status = EXIT_SUCCESS;
	}
	else
		exe_multiple_cmds(cmd_cnt, cmd_p, env, fds);
	dup2(fds[STD][R_FD], STDIN_FILENO);
	dup2(fds[STD][W_FD], STDOUT_FILENO);
}
