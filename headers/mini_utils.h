/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:42:34 by heson             #+#    #+#             */
/*   Updated: 2023/03/30 17:33:38 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_UTILS_H
# define MINI_UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include "../library/libft/libft.h"

void	set_termios(int echoctl_on);

char	*ft_strndup(const char *str, size_t size);
int     compare_strs(char *str1, char *str2);
char	*strjoin_n_free(char *s1, char *s2);
void	ft_free_str(char **arg);
int	    perror_n_return(char *err_pos, char *err_msg, int is_custom, int exit_status);
void	perror_n_exit(char *err_msg, int is_custom, int exit_status);

#endif