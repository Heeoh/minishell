/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:36:42 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/28 16:08:21 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* to do

print error
- exit status
	- init 0
	- syntax error - 258
	- command not found - 127
	- path permission denied - 126
	- ctrl + D - 0
	- ctrl + C - 1
- $?
- replace env 수정
built in 함수들 exit으로 -> exe_a_cmd void 가능 ->안됨 return으로 해야됨(안그럼 부모 프로세스 죽음)
- termios, old_ter, new_ter (clhild -> 나와야 됨)
awk, sed (...wait)
momory leak, norm (later)

*/

#include "../headers/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

int	g_exit_status = 0;

void leaks(void) {
	system("leaks minishell");
}

void	test_parsing_cmd(t_list *cmd_lst)
{
	for (t_list *p = cmd_lst; p; p=p->next) {
		// printf("%d\n", ((t_cmd *)p->content)->ac);
		for (int i=0; i<((t_cmd *)p->content)->ac; i++) {
			printf("%s, ", ((t_cmd *)p->content)->av[i]);
		}
		printf("\n");
		for (t_list *rd_p = ((t_cmd *)p->content)->rd; rd_p; rd_p = rd_p->next) {
			printf("(%d %s) ", ((t_redirection *)rd_p->content)->type,  ((t_redirection *)rd_p->content)->val);
		}
		printf("\n");
		// printf("in: %s, out: %s, heredoc: %s, append: %s\n", ((t_cmd *)p->content)->rd_in, ((t_cmd *)p->content)->rd_out, ((t_cmd *)p->content)->rd_heredoc, ((t_cmd *)p->content)->rd_append);
	}
}

void	set_termios(struct termios *org_term, struct termios *new_term)
{
	tcgetattr(STDOUT_FILENO, org_term);
	tcgetattr(STDOUT_FILENO, new_term);
	new_term->c_lflag &= ~(ECHOCTL);  // ICANON, ECHO 속성을 off
	new_term->c_cc[VMIN] = 1;               // 1 바이트씩 처리
	new_term->c_cc[VTIME] = 0;              // 시간은 설정하지 않음
}

int	main(int ac, char *av[], char *env[])
{
	char			*line;
	t_list			*cmd_lst;
	int				cmd_cnt;
	t_list			*env_lst;
	struct termios	terms[2];
	

	
	// atexit(leaks);
	ac = 0;
	av = 0;
	env_lst = init_env_lst(env);
	// init_rl_catch_signals();
	setting_signal();
	set_termios(&terms[0], &terms[1]);
	// tcsetattr(STDOUT_FILENO, TCSANOW, &terms[1]);
	// using_history()
	while (1) {
		cmd_lst = NULL;
		line = readline("minishell> ");
		if (line == NULL) {
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\033[12C", STDOUT_FILENO);
			printf("exit\n"); // CTRL + D
			break;
		}
		if (!ft_strncmp(line, "", 10)) {
				free(line);
				continue; 
		}
		add_history(line);
		cmd_cnt = parsing(line, &cmd_lst, env_lst);
		if (cmd_cnt < 0)
			continue ;
		// test_parsing_cmd(cmd_lst);
		// tcsetattr(STDOUT_FILENO, TCSANOW, &terms[0]);
		execute(cmd_cnt, cmd_lst, env_lst);
		// tcsetattr(STDOUT_FILENO, TCSANOW, &terms[1]);
		ft_lstclear(&cmd_lst, free_cmd_struct);
		ft_free_str(&line);
	}
	clear_history();
	ft_lstclear(&env_lst, free_env_var);
}