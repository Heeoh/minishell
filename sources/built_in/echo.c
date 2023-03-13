/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:11:11 by heson             #+#    #+#             */
/*   Updated: 2023/03/13 22:06:43 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../library/libft/libft.h"


// ' ', " ", env 처리
void	ft_echo(char *str, char option_n)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	if (!option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

// int main()
// {
//     ft_echo("hello", 1);
// }