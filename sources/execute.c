/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:26:11 by heson             #+#    #+#             */
/*   Updated: 2023/03/17 14:38:25 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/libft/libft.h"
#include "../library/get_next_line/get_next_line.h"
#include "../headers/minishell.h"
#include <unistd.h> // access
#include <stdio.h> //printf 
#include <fcntl.h> // open, write
#include <readline/readline.h>

void	print_error_n_exit(char *err_msg)
{
	printf("%s\n", err_msg);
	exit(0);
}

char	*find_path(char *cmd, char **env)
{
	char	*ret;
	char	**path_group;
	int		i;

	ret = 0;
	while (ft_strnstr(*env, "PATH", 4) == 0)
		env++;
	path_group = ft_split(*env, ':');
	i = -1;
	while (path_group[++i])
	{
		ret = ft_strjoin(path_group[i], "/");
		ret = ft_strjoin(ret, cmd);
		if (access(ret, F_OK) == 0)
			break ;
		free(ret);
	}
	i = -1;
	while (path_group[++i])
		free(path_group[i]);
	free(path_group);
	return (ret);
}

char	*create_heredoc_file(char *limiter)
{
	int		fd;
	char	*filename;
	char	*str;

	// open 시 이미 동일한 파일이 있을 경우 처리
	filename = ft_strdup("heredoc_tmp.txt");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		str = get_next_line(0);
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(fd, str, ft_strlen(str));
	}
	close(fd);
	return (filename);
}

void	do_redirection_in(char *val, int *fd, char is_heredoc)
{
	char	*filename;

	if (is_heredoc)
		filename = create_heredoc_file(val);
	else
		filename = val;
	*fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
		print_error_n_exit("file open error");
	if (dup2(*fd, STDIN_FILENO) < 0)
		print_error_n_exit("dup2 error");
}

void	do_redirection_out(char *filename, int *fd, char is_append)
{
	close(*fd);
	if (is_append)
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(*fd, STDOUT_FILENO) < 0)
		print_error_n_exit("dup2 error");
}

void	exe_a_cmd(t_cmd *cmd, char *env[])
{
	int		fd;
	char	*path;

	path = find_path(cmd->av[0], env);
	if (access(path, F_OK) != 0)
		print_error_n_exit("no such file");
	if (access(path, X_OK) != 0)
		print_error_n_exit("permission denied");
	if (cmd->rd_in)
		do_redirection_in(cmd->rd_in, &fd, 0);
	else if (cmd->rd_heredoc)
		do_redirection_in(cmd->rd_heredoc, &fd, 1);
	if (cmd->rd_out)
		do_redirection_out(cmd->rd_out, &fd, 0);
	else if (cmd->rd_append)
		do_redirection_out(cmd->rd_append, &fd, 1);
	// if (unlink(path) == -1)
	// 	ft_putendl_fd("unlink error", 2);
	execve(path, cmd->av, env);
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
void wait_processes(int child_cnt)
{
	int count;
	int status;

	count = 0;
	while (count < child_cnt)
	{
		if (wait(&status) == -1 || WIFEXITED(status) != 1)
			print_error_n_exit("wait error");
		count++;
	}
}

void	multiple_pipes(int cmd_cnt, t_list *cmd_p, char *env[], int pipes[][2])
{
	int	cmd_i;
	int	pid;
	int	done_cnt;

	cmd_i = 0;
	done_cnt = 0;
	while (cmd_i < cmd_cnt)
	{
		if (pipe(pipes[cmd_i % PIPE_N]) == -1)
			print_error_n_exit("pipe error");
		pid = fork();
		if (pid == -1)
			print_error_n_exit("fork error");
		else if (!pid) // child process
		{
			child_process(cmd_i, cmd_cnt, pipes, ((t_cmd *)cmd_p->content)->rd_heredoc != 0);
			exe_a_cmd((t_cmd *)cmd_p->content, env);
		}
		else if (pid) // parent process
			parent_process(cmd_i, pipes);
		cmd_i++;
		cmd_p = cmd_p->next;
	}
	wait_processes(cmd_cnt);
}

void    execute(int cmd_cnt, t_list *cmds, char *env[])
{
	int		i;
	int		pipes[PIPE_N][2];

	i = 0;
	while (i < PIPE_N)
	{
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
	if (cmd_cnt <= 0)
		return ;
	if (cmd_cnt == 1)
		exe_a_cmd((t_cmd *)cmds->content, env);
	else // pipe
		multiple_pipes(cmd_cnt, cmds, env, pipes);
}

t_cmd *create_cmd(char *str, char *in,  char *out,  char *heredoc,  char *append){
	t_cmd   *cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->av = ft_split(str, ' ');
	cmd->ac = 0;
	for (char **p = cmd->av; p && *p; p++) {
		cmd->ac++;
	}
	cmd->rd_in = (in) ? ft_strdup(in) : 0;
	cmd->rd_out = (out) ? ft_strdup(out) : 0; // ft_strdup("outfile.txt");
	cmd->rd_heredoc = (heredoc) ? ft_strdup(heredoc) : 0; //ft_strdup("end");
	cmd->rd_append = (append) ? ft_strdup(append) : 0; //ft_strdup("outfile.txt");
	return (cmd);
}

// int main(int ac, char *av[], char *env[]) {
// 	t_list *cmd_lst = NULL;
// 	// char * line;
	
// 	ac = 0;
// 	av = 0;
// 	ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("ls", 0, 0, 0, 0)));
// 	ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("cat", 0, 0, "end", "out.txt")));
// 	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("wc -l", 0, 0, 0, 0)));
// 	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("wc -l")));
// 	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
// 	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
// 	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
// 	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 5")));
// 	// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 5")));
	

// 	execute(ft_lstsize(cmd_lst), cmd_lst, env);
	
// 	// char is_done = 0;
// 	// // setting_signal();
// 	// while (1) {
// 	// 	line = readline("minishell> ");

// 		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("ls", 0, 0, 0, 0)));
// 		// // ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("cat", 0, 0, "end", "out.txt")));
// 		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("wc -l", 0, 0, 0, 0)));
// 		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("wc -l")));
// 		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
// 		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
// 		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 3")));
// 		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 5")));
// 		// ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("sleep 5")));
		
// 		// if (!is_done) {
// 			// execute(ft_lstsize(cmd_lst), cmd_lst, env);
// 	// 		is_done = 1;
// 	// 	}
// 	// }

// }

