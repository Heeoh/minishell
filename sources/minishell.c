// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   minishell.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/03/02 13:36:42 by jkim3             #+#    #+#             */
// /*   Updated: 2023/03/06 15:40:38 by heson            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <signal.h>
// #include <unistd.h>

// void sigint_handler(int sig) {
// 	if (sig != SIGINT)
// 		exit(0) ;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	return ;
// }

// void setting_signal()
// {
//     signal(SIGINT, sigint_handler);	// CTRL + C
//     signal(SIGQUIT, SIG_IGN);		// CTRL + /
// }

// int	main(int ac, char *av[], char *env[])
// {
// 	char * line;
	
// 	setting_signal();
// 	// printf("%d, %s\n", ac, av[0]);
// 	// for (int i=0; env[i]; i++) {
// 	// 	printf("%s\n", env[i]);
// 	// }
// 	// using_history()
// 	while (1) {
// 		line = readline("minishell> ");
// 		if (line == NULL) {
// 			printf("exit\n"); // CTRL + D
// 			break;
// 		}
// 		if (!strcmp(line, "")) {
// 				free(line);
// 				continue; 
// 		}
// 		add_history(line);
// 	}


// 	// clear_history();
// }