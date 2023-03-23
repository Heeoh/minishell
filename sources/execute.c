/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:26:11 by heson             #+#    #+#             */
/*   Updated: 2023/03/22 17:36:01 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	exe_a_cmd(t_cmd *cmd, t_list *env)
{
	int		fd;
	char	*path;

	path = find_path(cmd->av[0], env);
	if (access(path, F_OK) != 0)
		return (perror_n_return("no such file"));
	if (access(path, X_OK) != 0)
		return (perror_n_return("permission denied"));
	if (cmd->rd_in && do_redirection_in(cmd->rd_in, &fd, 0) < 0)
		return (ERROR);
	else if (cmd->rd_heredoc && do_redirection_in(cmd->rd_heredoc, &fd, 1) < 0)
		return (ERROR);
	if (cmd->rd_out && do_redirection_out(cmd->rd_out, &fd, 0) < 0)
		return (ERROR);
	else if (cmd->rd_append && do_redirection_out(cmd->rd_append, &fd, 1) < 0)
		return (ERROR);
	// if (unlink(path) == -1)
	// 	ft_putendl_fd("unlink error", 2);
	execve(path, cmd->av, envlst_2_arr(env));
	return (0);
}

void	child_process(int cmd_i, int cmd_cnt, int pipes[][2], char is_heredoc)
{
	if (cmd_i != 0 && !is_heredoc)
		dup2(pipes[(cmd_i + 1) % PIPE_N][0], STDIN_FILENO);
	if (cmd_i != cmd_cnt - 1)
		dup2(pipes[cmd_i % PIPE_N][1], STDOUT_FILENO);
	close(pipes[cmd_i % PIPE_N][0]);
	close(pipes[cmd_i % PIPE_N][1]);
}

void	parent_process(int cmd_i, int pipes[][2])
{
	close(pipes[cmd_i % PIPE_N][1]);
	if (cmd_i != 0)
		close(pipes[(cmd_i + 1) % PIPE_N][0]);
}

// 이럴 경우 예외 케이스가 없을까??
int	wait_processes(int child_cnt)
{
	int	count;
	int	status;

	count = 0;
	while (count < child_cnt)
	{
		if (wait(&status) == -1 || WIFEXITED(status) != 1)
			return (perror_n_return("wait error"));
		count++;
	}
	return (0);
}

/*
void	multiple_pipes(int cmd_cnt, t_list *cmd_p, t_list *env, int pipes[][2])
{
	int	cmd_i;
	int	pid;

	cmd_i = 0;
	while (cmd_i < cmd_cnt)
	{
		if (pipe(pipes[cmd_i % PIPE_N]) == -1)
			perror_n_return("pipe error");
		pid = fork();
		if (pid == -1)
			perror_n_return("fork error");
		else if (!pid) // child process
		{
			child_process(cmd_i, cmd_cnt, pipes,
				((t_cmd *)cmd_p->content)->rd_heredoc != 0);
			exe_a_cmd((t_cmd *)cmd_p->content, env);
		}
		else if (pid) // parent process
			parent_process(cmd_i, pipes);
		cmd_i++;
		cmd_p = cmd_p->next;
	}
	wait_processes(cmd_cnt);
}
*/

int	execute(int cmd_cnt, t_list *cmd_p, t_list *env)
{
	int	pipes[PIPE_N][2];
	int	cmd_i;
	int	pid;

	pipes[0][0] = -1;
	pipes[0][1] = -1;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
	cmd_i = -1;
	while (++cmd_i < cmd_cnt)
	{
		if (pipe(pipes[cmd_i % PIPE_N]) == -1)
			return (perror_n_return("pipe error"));
		pid = fork();
		if (pid == -1)
			return (perror_n_return("fork error"));
		else if (!pid) // child process
		{
			child_process(cmd_i, cmd_cnt, pipes,
				((t_cmd *)cmd_p->content)->rd_heredoc != 0);
			if (exe_a_cmd((t_cmd *)cmd_p->content, env) < 0)
				return (ERROR);
		}
		else if (pid) // parent process
			parent_process(cmd_i, pipes);
		cmd_p = cmd_p->next;
	}
	return (wait_processes(cmd_cnt));
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
