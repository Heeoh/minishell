/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:36:37 by heson             #+#    #+#             */
/*   Updated: 2022/10/17 11:55:35 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# else
#  if BUFFER_SIZE < 1
#   error INVALID BUFFER_SIZE!
#  endif
# endif

# define ERROR_I -1
# define ERROR_P NULL
# define TRUE 1
# define FALSE 0

typedef struct s_Buf {
	char			*data;
	int				data_len;
	struct s_Buf	*next;
}	t_Buf;

typedef struct s_Lst {
	t_Buf	*lst;
	t_Buf	*last;
}	t_Lst;

typedef struct s_Info {
	int		fd;
	size_t	buf_size;
}	t_Info;

char	*my_strcat(char *dst, char const *src, size_t n);
t_Buf	*add_buf(t_Lst *buflst, char *data, size_t data_len);
char	data_2_buflst(char	*data, t_Lst *buflst, t_Buf **ep, size_t *line_len);
t_Buf	*find_next_line_buf(t_Buf *buflst, size_t *line_len);
void	free_buflst(t_Buf **buflst, t_Buf *new_head);

char	read_bufsize(t_Info info, char **data);
t_Buf	*read_line(t_Info info, t_Lst *buflst, size_t *line_len);
char	*integrate_to_line(t_Buf *buflst, t_Buf *ep, size_t line_len);
char	*get_line(t_Info info, t_Lst *buflst);
char	*get_next_line(int fd);

#endif