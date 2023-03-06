/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:15:33 by heson             #+#    #+#             */
/*   Updated: 2023/02/15 15:23:07 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf_utils.h"

size_t	my_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (s && *s++)
		cnt++;
	return (cnt);
}