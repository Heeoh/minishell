/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:26:11 by heson             #+#    #+#             */
/*   Updated: 2023/03/09 17:20:02 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/libft/libft.h"
#include "../library/get_next_line/get_next_line.h"
#include "../headers/minishell.h"
#include <unistd.h> // access
#include <stdio.h> //printf 
#include <fcntl.h> // open, write

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
	// PATH value 찾기
	while (ft_strnstr(*env, "PATH", 4) == 0)
		env++;
	// PATH value에서 해당 함수 실행 파일 경로 찾기
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
	*fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error_n_exit("file open error");
	if (dup2(*fd, STDIN_FILENO) < 0)
		print_error_n_exit("dup2 error");
}

void	do_redirection_out(char *filename, int *fd, char is_append)
{
	close(*fd);
	if (is_append)
		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND);
	else
		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
	if (dup2(*fd, STDOUT_FILENO) < 0)
		print_error_n_exit("dup2 error");
}

void	exe_a_cmd(t_cmd *cmd, char *env[])
{
	int	fd;

	// for (char **p = cmd->av; p && *p; p++) {
	// 	ft_putstr_fd(*p, 2);
	// }
	// printf("\n");
	char *path = find_path(cmd->av[0], env);
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
	execve(path, cmd->av, env);
}

void    execute(int cmd_cnt, t_list *cmds, char *env[])
{
	int	i;
	int fds[2][2];
	int pid;
	t_list *cmd_p;

	i = 0;
	fds[0][0] = -1;
	fds[0][1] = -1;
	fds[1][0] = -1;
	fds[1][1] = -1;
	cmd_p = cmds;
	if (cmd_cnt <= 0)
		return ;
	if (cmd_cnt == 1)
		exe_a_cmd((t_cmd *)cmds->content, env);
	else // pipe
	{
		while (i < cmd_cnt)
		{
			if (pipe(fds[i % 2]) == -1)
			printf("pipe failure\n");
			pid = fork();
			if (pid == -1)
				printf("fork failure\n");
			else if (!pid)
			{
				if (i == 0)
				{
					// printf("child 1\n");
					close(fds[(i + 1) % 2][0]);
					close(fds[(i + 1) % 2][1]);
					close(fds[i % 2][0]);
					dup2(fds[i % 2][1], STDOUT_FILENO);
					close(fds[i % 2][1]);
				}
				else if (i != cmd_cnt - 1)
				{
					// printf("child %d\n", i+1);
					close(fds[(i + 1) % 2][1]); // close write end of first pipe
					dup2(fds[(i + 1) % 2][0], STDIN_FILENO);
					close(fds[(i + 1) % 2][0]); // close original read end of first pipe
					close(fds[i % 2][0]); // close read end of second pipe
					dup2(fds[i % 2][1], STDOUT_FILENO);
					close(fds[i % 2][1]); // close original write end of second pipe
				}
				else {
					// printf("child %d\n", i+1);
					close(fds[(i + 1) % 2][1]); // close write end of first pipe
					dup2(fds[(i + 1) % 2][0], STDIN_FILENO);
					close(fds[(i + 1) % 2][0]); // close original read end of first pipe
					close(fds[i % 2][0]); // close read end of second pipe
					close(fds[i % 2][1]); // close original write end of second pipe
				}
				// write(2, "d\n", 2);
				exe_a_cmd((t_cmd *)cmd_p->content, env);
				// return (0);
			}
			else if (pid)
			{
				if (waitpid(pid, NULL, WNOHANG) == -1)
					printf("child process error\n");
			}
			i++;
			cmd_p = cmd_p->next;
		}
	}
}

t_cmd *create_cmd(char *str){
	t_cmd   *cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->av = ft_split(str, ' ');
	cmd->ac = 0;
	for (char **p = cmd->av; p && *p; p++) {
		cmd->ac++;
	}
	cmd->rd_in = 0; //ft_strdup("infile.txt");
	cmd->rd_out = 0; // ft_strdup("outfile.txt");
	cmd->rd_heredoc = 0; //ft_strdup("end");
	cmd->rd_append = 0; //ft_strdup("outfile.txt");
	return (cmd);
}

int main(int ac, char *av[], char *env[]) {
	t_list *cmd_lst = NULL;

	ac = 0;
	av = 0;
	ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("ls")));
	ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("cat")));
	ft_lstadd_back(&cmd_lst, ft_lstnew(create_cmd("wc -l")));

	execute(3, cmd_lst, env);

}

