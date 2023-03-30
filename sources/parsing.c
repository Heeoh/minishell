/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:45:17 by jkim3             #+#    #+#             */
/*   Updated: 2023/03/30 17:45:05 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	parsing(char *line, t_list **cmd, t_list *env_lst)
{
	t_list	*tk_lst;
	int		cmd_cnt;

	tk_lst = NULL;
	if (tokenizing(&tk_lst, line, env_lst) < 0)
		return (ERROR);
	// for (t_list *p = tk_lst; p; p = p->next)
	// 	printf("%s\n", (char *)p->content);
	cmd_cnt = init_cmd_lst(cmd, tk_lst);
	ft_lstclear(&tk_lst, free);
	return (cmd_cnt);
}

int	init_cmd_lst(t_list **cmd, t_list *tk_lst)
{
	t_list	*tk_p;
	t_cmd	*new_cmd;
	int		cmd_cnt;

	tk_p = tk_lst;
	new_cmd = NULL;
	cmd_cnt = 0;
	while (tk_p)
	{
		if (set_cmd_val(&tk_p, &new_cmd) < 0)
			return (ERROR);
		cus_ft_lstadd_back(cmd, new_cmd);
		cmd_cnt++;
		if (tk_p)
			tk_p = tk_p->next;
	}
	return (cmd_cnt);
}


// int main(int ac, char *av[], char *env[])
// {
// 	t_list	*cmds;

// 	ac = 0;
// 	av = 0;
// 	t_list *envlst = init_env(env);
// 	cmds = NULL;
// 	parsing("<<end cat > out | echo $USER | echo 'hello'", &cmds, envlst);
// 	for (t_list *p = cmds; p; p=p->next) {
// 		for (int i=0; i<((t_cmd *)p->content)->ac; i++) {
// 			printf("%s, ", ((t_cmd *)p->content)->av[i]);
// 		}
// 		printf("\n");
// 		printf("in: %s, out: %s, heredoc: %s, append: %s\n", ((t_cmd *)p->content)->rd_in, ((t_cmd *)p->content)->rd_out, ((t_cmd *)p->content)->rd_heredoc, ((t_cmd *)p->content)->rd_append);
// 	}
// }
