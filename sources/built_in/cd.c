/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:05:31 by heson             #+#    #+#             */
/*   Updated: 2023/03/15 13:49:59 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> // perror

// error 출력 부분 bash 형태에 맞게 손 봐야함
int	ft_cd(char *path)
{
	// printf("from: %s\n", getcwd(0, 256));
	if (chdir(path) < 0)
	{
    	perror(0);
    	return -1;
	}
    // printf("to: %s\n", getcwd(0, 256));
	return (0);
}

// int main(int ac, char *av[]) {
// 	if (ac != 2)
// 		return (1);
// 	if (ft_cd(av[1]) < 0)
// 		return (1);
// }