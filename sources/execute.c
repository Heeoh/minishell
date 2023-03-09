/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:26:11 by heson             #+#    #+#             */
/*   Updated: 2023/03/06 19:17:23 by heson            ###   ########.fr       */
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
	t_cmt *cmd_p;

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
		while (++i < cmd_cnt)
		{
			if (pipe(fds[i % 2]) == -1)
				printf("error in pipe\n");
			pid = fork();
			if (pid < 0) // error
				printf("error in fork\n");
			else if (pid == 0) // child
			{
				// stdin -> fds[another][0]
				// stdout -> fds[cur][1]
				// exe
				// close fds[another][0], fds[cur][1]
				// return
				dup2(fds[(i+1) % 2][0], STDIN_FILENO);
				dup2(fds[i % 2][1], STDOUT_FILENO);
				exe_a_cmd(cmd_p, env);
				close(fds[(i+1) % 2][0]);
				close(fds[i % 2][1]);
				return;
			}
			else if (pid > 0) // parent
			{
				if (waitpid(pid, NULL, WNOHANG) == -1)
					printf("error in waitpid\n");
			} 

		}	
	}
}

int main(int ac, char *av[], char *env[]) {
	t_list *cmd_lst;
	t_list *new;
	t_cmd   cmd;

	cmd.ac = 1;
	cmd.av = ft_split("ls");
	cmd.rd_in = 0; //ft_strdup("infile.txt");
	cmd.rd_out = 0; // ft_strdup("outfile.txt");
	cmd.rd_heredoc = 0; //ft_strdup("end");
	cmd.rd_append = 0; //ft_strdup("outfile.txt");
	new = ft_lstnew(&cmd);
	ft_lstadd_front(&cmd_lst, new);

	cmd.ac = 1;
	cmd.av = ft_split("cat");
	cmd.rd_in = 0; //ft_strdup("infile.txt");
	cmd.rd_out = 0; // ft_strdup("outfile.txt");
	cmd.rd_heredoc = 0; //ft_strdup("end");
	cmd.rd_append = 0; //ft_strdup("outfile.txt");
	new = ft_lstnew(&cmd);
	ft_lstadd_front(&cmd_lst, new);

	execute(1, cmd_lst, env);

}


/*
parsing!! 
- t_cmd의 av[ac] = 0 -> 마지막임을 알려줘야 함
- execve 에서 커멘드를 문자열 배열 형태로 받기 때문에 av도 동일한 형식이어야 함

- redirection을 하나의 커멘드로 볼것인가..! 그건 아닌 거 같은데

*/