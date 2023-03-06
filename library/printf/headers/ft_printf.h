/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:14:15 by heson             #+#    #+#             */
/*   Updated: 2022/12/14 16:02:07 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>

# define ERROR_P NULL
# define ERROR_I -1
# define TRUE 1
# define FALSE 0

typedef enum e_types {
	CHAR = 0,
	STR,
	POINTER,
	DECIMAL,
	INT,
	U_INT,
	LOWER_X,
	UPPER_X,
	PERCENT,
	TYPE_N,
	TYPE_INIT = -1
}	t_types;

typedef enum e_flags {
	MINUS = 0,
	ZERO,
	PRECISION,
	HASH,
	PLUS,
	SPACE,
	FLAG_N
}	t_flags;

typedef struct s_format {
	t_types	type;
	int		field_width;
	int		flags[FLAG_N];
}	t_format;

typedef struct s_data {
	char	*str;
	size_t	len;
}	t_data;

int	ft_printf(const char *str, ...);

#endif