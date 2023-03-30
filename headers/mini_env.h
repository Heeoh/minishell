/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:40:06 by heson             #+#    #+#             */
/*   Updated: 2023/03/30 15:46:01 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_ENV_H
# define MINI_ENV_H

# include "../library/libft/libft.h"
# include "../headers/mini_utils.h"

extern int	g_exit_status;

typedef struct s_env_var {
	char    *key;
	char    *value;
	int		is_tmp;
}   t_env_var;

t_env_var	*create_env_var(char *arg);
t_env_var	*create_env_var_struct(char *key, char *val, int is_tmp);
void		free_env_var(void	*arg);
void		*copy_env_var(void *arg);

char		*ft_getenv(t_list *env_lst, char *key);
int			ft_putenv(t_list *env_lst, char *arg);
char		*replace_env(t_list *env_lst, char *data);

t_list		*init_env_lst(char *org_env[]);
void		sort_env_lst(t_list **env_lst);
void		print_env_lst(t_list *env_lst, int env_flag);
char		**envlst_2_arr(t_list *env_lst);




#endif