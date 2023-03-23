/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:42:34 by heson             #+#    #+#             */
/*   Updated: 2023/03/23 14:44:28 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../library/libft/libft.h"

char	*ft_strndup(const char *str, size_t size);
char	*strjoin_n_free(char *s1, char *s2);
void	ft_free_str(char **arg);
int		perror_n_return(char *err_msg);