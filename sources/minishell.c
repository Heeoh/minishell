/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:36:42 by jkim3             #+#    #+#             */
/*   Updated: 2023/04/01 20:45:10 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/mini_parsing.h"

int	g_exit_status = 0;

static	void	init_mini_main(int ac, char *av[],
							char *env[], t_list **env_lst)
{
	ac = 0;
	av = 0;
	set_ctrl(0, sigint_handler, SIG_IGN);
	*env_lst = init_env_lst(env);
}

static	void	reset(t_list **cmd_lst, char **line)
{
	set_ctrl(0, sigint_handler, SIG_IGN);
	ft_lstclear(cmd_lst, free_cmd_struct);
	ft_free_str(line);
}

static	int	ctrl_d_minishell(void)
{
	ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[11C", STDOUT_FILENO);
	printf("exit\n");
	return (1);
}

static	void	clear(t_list *env_lst)
{
	clear_history();
	ft_lstclear(&env_lst, free_env_var);
}

int	main(int ac, char *av[], char *env[])
{
	char			*line;
	t_list			*cmd_lst;
	int				cmd_cnt;
	t_list			*env_lst;

	init_mini_main(ac, av, env, &env_lst);
	while (1)
	{
		cmd_lst = NULL;
		line = readline("minishell> ");
		if (line == NULL && ctrl_d_minishell())
			break ;
		if (ft_strncmp(line, "", 10) != 0)
		{
			add_history(line);
			cmd_cnt = parsing(line, &cmd_lst, env_lst);
			if (cmd_cnt > 0)
				execute(cmd_cnt, cmd_lst, env_lst);
		}
		reset(&cmd_lst, &line);
	}
	clear(env_lst);
}
