/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:36:42 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/20 17:51:11 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void sigint_handler(int sig) {
	if (sig != SIGINT)
		exit(0) ;
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
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
		for (t_list *p = cmd_lst; p; p=p->next) {
			for (int i=0; i<((t_cmd *)p->content)->ac; i++) {
				printf("%s, ", ((t_cmd *)p->content)->av[i]);
			}
			printf("\n");
			printf("in: %s, out: %s, heredoc: %s, append: %s\n", ((t_cmd *)p->content)->rd_in, ((t_cmd *)p->content)->rd_out, ((t_cmd *)p->content)->rd_heredoc, ((t_cmd *)p->content)->rd_append);
		}
		add_history(line);
		// exe
		ft_lstclear(&cmd_lst, free_cmd_struct);
	}


	// clear_history();
}