/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:26:11 by heson             #+#    #+#             */
/*   Updated: 2023/03/28 22:08:02 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/built_in.h"

extern int g_exit_status;

int	is_built_in(char *cmd)
{
	char	*lower_cmd;
	int		i;

	if (!cmd || !*cmd)
		return (-1);
	lower_cmd = (char *)ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!lower_cmd)
		return (-1);
	i = 0;
	while (cmd[i])
	{
		lower_cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	if (ft_strncmp("echo", lower_cmd, 10) == 0)
		return (BI_ECHO);
	if (ft_strncmp("env", lower_cmd, 10) == 0)
		return (BI_ENV);
	if (ft_strncmp("pwd", lower_cmd, 10) == 0)
		return (BI_PWD);
	if (ft_strncmp("exit", cmd, 10) == 0)
		return (BI_EXIT);
	if (ft_strncmp("cd", cmd, 10) == 0)
		return (BI_CD);
	if (ft_strncmp("unset", cmd, 10) == 0)
		return (BI_UNSET);
	if (ft_strncmp("export", cmd, 10) == 0)
		return (BI_EXPORT);
	return (-1);
}

int	exe_built_in(t_cmd *cmd_p, t_list *env_lst, int cmd_type)
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

int	exe_a_cmd(t_cmd *cmd, t_list *env, int fd_stdin)
{
	int				fd;
	char			*path;
	t_list			*rd_lst_p;
	t_redirection	*rd;
	int				is_builtin;

	signal(SIGINT, SIG_DFL);
	is_builtin = is_built_in(cmd->av[0]);
	if (is_builtin < 0)
	{
		path = find_path(cmd->av[0], env);
		if (access(path, F_OK) != 0)
			return (perror_n_return(cmd->av[0], 0, 127));
		if (access(path, X_OK) != 0)
			return (perror_n_return(cmd->av[0], 0, 126));
	}
	fd = -1;
	rd_lst_p = cmd->rd;
	while(rd_lst_p)
	{
		if (fd > 0)
			close(fd);
		rd = (t_redirection *)rd_lst_p->content;
		if (rd->type == RD_IN && do_redirection_in(rd->val, &fd, 0, fd_stdin) < 0)
			return (ERROR);
		else if (rd->type == RD_HEREDOC && do_redirection_in(rd->val, &fd, 1, fd_stdin) < 0)
			return (ERROR);
		else if (rd->type == RD_OUT && do_redirection_out(rd->val, &fd, 0) < 0)
			return (ERROR);
		else if (rd->type == RD_APPEND && do_redirection_out(rd->val, &fd, 1) < 0)
			return (ERROR);
		rd_lst_p = rd_lst_p->next;
	}
	set_termios(1);
	signal(SIGQUIT, SIG_DFL);
	if (!(cmd->av) || !*(cmd->av))
		return (ERROR);
	if (is_builtin >= 0)
		return(exe_built_in(cmd, env, is_builtin));
	return (execve(path, cmd->av, envlst_2_arr(env)));
}

int	child_process(int cmd_i, int cmd_cnt, int pipes[][2])
{
	if (cmd_i != 0)
	{
		if( dup2(pipes[(cmd_i + 1) % PIPE_N][R_FD], STDIN_FILENO) < 0)
			perror_n_exit(NULL, 0, EXIT_FAILURE);
	}
	if (cmd_i != cmd_cnt - 1)
	{
		if (dup2(pipes[cmd_i % PIPE_N][W_FD], STDOUT_FILENO) < 0)
			perror_n_exit(NULL, 0, EXIT_FAILURE);
	}
	close(pipes[cmd_i % PIPE_N][R_FD]);
	close(pipes[cmd_i % PIPE_N][W_FD]);
	return (0);
}

void	parent_process(int cmd_i, int pipes[][2])
{
	close(pipes[cmd_i % PIPE_N][W_FD]);
	if (cmd_i != 0)
		close(pipes[(cmd_i + 1) % PIPE_N][R_FD]);
}

// 이럴 경우 예외 케이스가 없을까??
// ctrl + D 들어왔을 때!!!!!!
int wait_processes(int child_cnt, int pid)
{
    int count;
    int status;
	int	wait_pid;
    count = 0;
	
    while (count < child_cnt)
    {
		wait_pid = wait(&status);
        if (wait_pid == -1)
            perror_n_exit("wait error", 0, status);
		if (WIFEXITED(status) && (wait_pid == pid))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
			{
				ft_putstr_fd("\n", 2);
				g_exit_status = 130;
			}
			else if (WTERMSIG(status) == 3)
			{
				ft_putstr_fd("Quit: 3\n", 2);
				g_exit_status = 131;
			}
			else
				g_exit_status = WTERMSIG(status);
		}
        count++;
    }
    return (0);
}

int	multiple_pipes(int cmd_cnt, t_list *cmd_p, t_list *env, int fds[][2])
{
	int	cmd_i;
	int	pid;

	cmd_i = -1;
	while (++cmd_i < cmd_cnt)
	{
		if (pipe(fds[cmd_i % PIPE_N]) == -1)
			return (perror_n_return("pipe error", 0, EXIT_FAILURE));
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == -1)
			return (perror_n_return("fork error", 0, EXIT_FAILURE));
		else if (!pid) // child process
		{
			// setting_signal_exe();
			child_process(cmd_i, cmd_cnt, fds);
			if (exe_a_cmd((t_cmd *)cmd_p->content, env, fds[STD][R_FD]) < 0)
				exit(g_exit_status);
		}
		else if (pid) // parent process
			parent_process(cmd_i, fds);
		cmd_p = cmd_p->next;
	}
	return (wait_processes(cmd_cnt, pid));
}

void	execute(int cmd_cnt, t_list *cmd_p, t_list *env)
{
	int	fds[PIPE_N + 1][2];

	fds[0][R_FD] = -1;
	fds[0][W_FD] = -1;
	fds[1][R_FD] = -1;
	fds[1][W_FD] = -1;
	fds[STD][R_FD] = dup(STDIN_FILENO);
	fds[STD][W_FD] = dup(STDOUT_FILENO);
	if (cmd_cnt == 1 && is_built_in(((t_cmd *)cmd_p->content)->av[0]) >= 0)
	{
		g_exit_status = exe_a_cmd(cmd_p->content, env, STDIN_FILENO);
		dup2(fds[STD][R_FD], STDIN_FILENO);
		dup2(fds[STD][W_FD], STDOUT_FILENO);
		// return (ret);
	}
	else
		multiple_pipes(cmd_cnt, cmd_p, env, fds);
	// return (0);
	
}

/*
int main(int ac, char *av[], char *env[])
{
	t_list *cmd_lst = NULL;
	// char * line;
	ac = 0;
	av = 0;
	ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("ls", 0, 0, 0, 0)));
	ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("cat", 0, 0, "end", "out.txt")));
	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("wc -l", 0, 0, 0, 0)));
	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("wc -l")));
	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 5")));
	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 5")));
	

	execute(ft_lstsize(cmd_lst), cmd_lst, env);
	
	// char is_done = 0;
	// // setting_signal();
	// while (1) {
	// 	line = readline("minishell> ");

		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("ls", 0, 0, 0, 0)));
		// // ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("cat", 0, 0, "end", "out.txt")));
		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("wc -l", 0, 0, 0, 0)));
		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("wc -l")));
		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 5")));
		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 5")));
		
		// if (!is_done) {
			// execute(ft_lstsize(cmd_lst), cmd_lst, env);
	// 		is_done = 1;
	// 	}
	// }

}*/
