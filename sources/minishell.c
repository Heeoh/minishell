/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:36:42 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/21 17:24:40 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	init_rl_catch_signals(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
}

void sigint_handler(int sig) {
	if (sig != SIGINT)
		exit(0) ;
	ft_putstr_fd("\n", STDOUT_FILENO);	
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void setting_signal()
{
    signal(SIGINT, sigint_handler);	// CTRL + C
    signal(SIGQUIT, SIG_IGN);		// CTRL + /
}

void	free_cmd_struct(void *arg)
{
	t_cmd	*target;
	int		i;

	target = (t_cmd *)arg;
	i = 0;
	while (i < target->ac)
		free(target->av[i++]);
	if (target->rd_in)
		free(target->rd_in);
	if (target->rd_out)
		free(target->rd_out);
	if (target->rd_heredoc)
		free(target->rd_heredoc);
	if (target->rd_append)
		free(target->rd_append);
}

int	main(int ac, char *av[], char *env[])
{
	char	*line;
	t_list	*cmd_lst;
	t_list	*env_lst;
	
	ac = 0;
	av = 0;
	init_rl_catch_signals();
	setting_signal();
	env_lst = init_env(env);
	// using_history()
	while (1) {
		cmd_lst = NULL;
		line = readline("minishell> ");
		if (line == NULL) {
			printf("exit\n"); // CTRL + D
			break;
		}
		if (!strcmp(line, "")) {
				free(line);
				continue; 
		}
		parsing(line, &cmd_lst, env_lst);
		// for (t_list *p = cmd_lst; p; p=p->next) {
		// 	for (int i=0; i<((t_cmd *)p->content)->ac; i++) {
		// 		printf("%s, ", ((t_cmd *)p->content)->av[i]);
		// 	}
		// 	printf("\n");
		// 	printf("in: %s, out: %s, heredoc: %s, append: %s\n", ((t_cmd *)p->content)->rd_in, ((t_cmd *)p->content)->rd_out, ((t_cmd *)p->content)->rd_heredoc, ((t_cmd *)p->content)->rd_append);
		// }
		add_history(line);
		// exe
		ft_lstclear(&cmd_lst, free_cmd_struct);
	}


	// clear_history();
}