/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:35:12 by heson             #+#    #+#             */
/*   Updated: 2023/03/06 18:58:21 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	read_bufsize(t_Info info, char **data)
{
	int	read_size;

	*data = (char *)malloc(info.buf_size * sizeof(char) + 1);
	if (!*data)
		return (ERROR_I);
	read_size = read(info.fd, *data, info.buf_size);
	if (read_size < 0)
		return (ERROR_I);
	(*data)[read_size] = '\0';
	if (!read_size)
		return (TRUE);
	return (FALSE);
}

t_Buf	*read_line(t_Info info, t_Lst *buflst, size_t *line_len)
{
	char	is_line_end;
	char	*data;
	t_Buf	*buf_ep;

	is_line_end = FALSE;
	buf_ep = NULL;
	while (is_line_end == FALSE)
	{
		is_line_end = read_bufsize(info, &data);
		if (is_line_end == TRUE)
		{
			if (buflst->lst)
				buf_ep = buflst->last;
			else
				buf_ep = add_buf(buflst, data, 1);
		}
		else if (is_line_end == FALSE)
			is_line_end = data_2_buflst(data, buflst, &buf_ep, line_len);
		if (data)
			free(data);
	}
	if (is_line_end == ERROR_I)
		return (ERROR_P);
	return (buf_ep);
}

char	*integrate_to_line(t_Buf *buflst, t_Buf *ep, size_t line_len)
{
	char	*line;
	char	*line_p;
	t_Buf	*buflst_p;

	if (!buflst || buflst->data[0] == '\0' || ep == ERROR_P)
		return (NULL);
	line = (char *)malloc(line_len * sizeof(char) + 1);
	if (!line)
		return (ERROR_P);
	line_p = line;
	buflst_p = buflst;
	while (buflst_p && buflst_p != ep->next)
	{
		line_p = my_strcat(line_p, buflst_p->data, buflst_p->data_len);
		buflst_p = buflst_p->next;
	}
	*line_p = '\0';
	return (line);
}

char	*get_line(t_Info info, t_Lst *buflst)
{
	char			*line;
	size_t			line_len;
	t_Buf			*buf_ep;

	line = NULL;
	line_len = 0;
	buf_ep = NULL;
	if (buflst->lst)
	{
		if (buflst->lst->data[0] == '\0')
		{
			free_buflst(&(buflst->lst), NULL);
			return (NULL);
		}
		buf_ep = find_next_line_buf(buflst->lst, &line_len);
	}
	if (!buf_ep)
		buf_ep = read_line(info, buflst, &line_len);
	line = integrate_to_line(buflst->lst, buf_ep, line_len);
	if (buf_ep && line)
		free_buflst(&(buflst->lst), buf_ep->next);
	else
		free_buflst(&(buflst->lst), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	t_Info			info;
	static t_Lst	buflst;
	char			*line;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	info.fd = fd;
	info.buf_size = BUFFER_SIZE;
	line = get_line(info, &buflst);
	if (line && *line)
		return (line);
	return (NULL);
}

/*
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h> 

int main() {
	// size_t buf_size = 42;
	int fd = open("test.txt", O_RDONLY);
	// close(fd);
	// fd = 100;
	while (1) {
		char *res = get_next_line(fd);
		if (!res) break;
		printf("%s", res);
		free (res);
		res = NULL;
	}

	// while (1);
}
//*/