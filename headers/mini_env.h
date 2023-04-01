/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:40:06 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 18:51:43 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_ENV_H
# define MINI_ENV_H

# include "../library/libft/libft.h"
# include "mini_utils.h"

typedef struct s_env_var {
	char	*key;
	char	*value;
	int		is_tmp;
}	t_env_var;

// env
char		*ft_getenv(t_list *env_lst, char *key);
int			ft_putenv(t_list *env_lst, char *arg);
char		*replace_env(t_list *env_lst, char *data);

// env_var
t_env_var	*create_env_var(char *arg);
t_env_var	*create_env_var_struct(char *key, char *val, int is_tmp);
void		free_env_var(void	*arg);
void		*copy_env_var(void *arg);

// env_lst
t_list		*init_env_lst(char *org_env[]);
void		sort_env_lst(t_list **env_lst);
void		print_env_lst(t_list *env_lst, int env_flag);
char		**envlst_2_arr(t_list *env_lst);

// env_utils
int			is_var_char(char ch);
int			is_valid_key(char *key);
void		split_lst(t_list *source, t_list **front, t_list **back);
t_list		*merge(t_list *a, t_list *b);

#endif