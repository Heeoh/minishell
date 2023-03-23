/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:36:42 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/23 20:41:50 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* to do


<
>f1>f2>f3 -> file 3개 만들어져야됨 (out, append)
in - 마지막 파일을 읽어오지만, 이전 파일이 없을 경우 error
heredoc - limiter 순차적으로 받고 이전 limiter 이후부터 마지막 limiter 까지 값이 input으로 넘어감


*/

#include "../headers/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


void leaks(void) {
	system("leaks minishell");
}

void	test_parsing_cmd(t_list *cmd_lst)
{
	for (t_list *p = cmd_lst; p; p=p->next) {
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
	init_rl_catch_signals();
	env_lst = init_env_lst(env);
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
		cmd_cnt = parsing(line, &cmd_lst, env_lst);
		test_parsing_cmd(cmd_lst);
		add_history(line);
		execute(cmd_cnt, cmd_lst, env_lst);
		ft_lstclear(&cmd_lst, free_cmd_struct);
	}

	// clear_history();
}