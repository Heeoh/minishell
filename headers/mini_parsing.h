/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:13:55 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 20:45:15 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PARSING_H
# define MINI_PARSING_H

# include "minishell.h"

typedef struct s_tokenizer {
	char	*line;
	int		quote;
	char	*sp;
	char	*tk_content;
	int		tk_size;
}	t_tokenizer;

// parsing
int				parsing(char *line, t_list **cmds, t_list *env_lst);
int				init_cmd_lst(t_list **cmd, t_list *tk_lst);

// tokenizing
int				tokenizing(t_list **tk_lst, char *line, t_list *env_lst);
t_tokenizer		*init_tokenizer(char *line);
int				tokenizing_quote(t_list *env_lst, t_tokenizer **tokenizer);
void			push_token_back(t_list *env_lst, t_list **tk_lst,
					t_tokenizer *tokenizer);
char			*get_token(t_list *env_lst,
					t_tokenizer *tokenizer, int in_quote);

// create_free_cmd
t_redirection	*create_rd(int type, char *val);
void			free_rd_struct(void *arg);
t_cmd			*create_cmd_struct(void);
void			free_cmd_struct(void *arg);

// cmd
int				set_cmd_val(t_list **tk_lst, t_cmd **cmd);
int				set_cmd_av(t_list *tk_p, char **av[], int ac);
int				set_cmd_redirection(char *type, char *val, t_list **rd_lst);
int				set_cmd_pipe(t_list **tk_lst, t_list *tk_p, t_cmd **cmd);

// parsing_utils
int				is_quote(char q, int quote);
int				is_token_separator(char c);
int				is_redirection(char *arg);

#endif