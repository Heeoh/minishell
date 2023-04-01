/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:42:34 by heson             #+#    #+#             */
/*   Updated: 2023/04/01 19:10:02 by jkim3            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_UTILS_H
# define MINI_UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include "../library/libft/libft.h"

void	set_termios(int echoctl_on);
char	*ft_strndup(const char *str, size_t size);
int		compare_strs(char *str1, char *str2);
char	*strjoin_n_free(char *s1, char *s2);
void	ft_free_str(char **arg);
int		perror_n_return(char *err_pos, char *err_msg,
			int is_custom, int exit_status);
void	perror_n_exit(char *err_msg, int is_custom, int exit_status);
void	cus_ft_lstadd_back(t_list **lst, void *content);
int		per_n_ret(char *pos, char *msg1, char *msg2, int exit_status);

#endif