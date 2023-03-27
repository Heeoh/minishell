/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:36:42 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/27 20:19:48 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* to do

print error
exit status
	- init 0
	- syntax error - 258
	- command not found - 127
	- path permission denied - 126
built in 함수들 exit으로 -> exe_a_cmd void 가능
termios
awk, sed
momory leak, norm

*/

#include "../headers/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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

int	main(int ac, char *av[], char *env[])
{
	char	*line;
	t_list	*cmd_lst;
	int		cmd_cnt;
	t_list	*env_lst;
	
	// atexit(leaks);
	ac = 0;
	av = 0;
	env_lst = init_env_lst(env);
	init_rl_catch_signals();
	setting_signal();
	// using_history()
	while (1) {
		cmd_lst = NULL;
		line = readline("minishell> ");
		if (line == NULL) {
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
		execute(cmd_cnt, cmd_lst, env_lst);
		ft_lstclear(&cmd_lst, free_cmd_struct);
	}
	clear_history();
	ft_lstclear(&env_lst, free_env_var);
}