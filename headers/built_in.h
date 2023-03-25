/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:46:35 by heson             #+#    #+#             */
/*   Updated: 2023/03/25 01:41:26 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

enum e_builtin_ft {
	BI_CD = 0,
	BI_ECHO,
	BI_ENV,
	BI_EXIT,
	BI_EXPORT,
	BI_PWD,
	BI_UNSET,
	BI_CNT
};

int ft_export(t_cmd *cmd, t_list *env);
int	ft_pwd(void);
int	ft_exit(t_cmd *cmd);
int	ft_env(t_list *env);
int	ft_echo(t_cmd *cmd);
int	ft_cd(char *path, t_list *env);
int	ft_unset(t_cmd *cmd, t_list **env_lst);


#endif
