/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:40:06 by heson             #+#    #+#             */
/*   Updated: 2023/03/16 22:01:08 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_ENV_H
# define MINI_ENV_H

# include "../library/libft/libft.h"
# include <stdio.h>

typedef struct s_env_var {
    char    *key;
    char    *value;
	char	is_tmp;
}   t_env_var;

void	free_env_var(void	*arg);
t_env_var	*create_env_var_struct(char *key, char *val, char is_tmp);
t_env_var	*create_env_var(char *arg);
void	*copy_env_var(void *arg);
char	*ft_getenv(t_list *env_lst, char *key);
void	sort_env_lst(t_list **env_lst);
void	print_env_lst(t_list *env_lst);

#endif