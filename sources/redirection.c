/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:16:55 by heson             #+#    #+#             */
/*   Updated: 2023/03/13 17:29:24 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// char	*create_heredoc_file(char *limiter)
// {
// 	int		fd;
// 	char	*filename;
// 	char	*str;

// 	// open 시 이미 동일한 파일이 있을 경우 처리
// 	filename = ft_strdup("heredoc_tmp.txt");
// 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	while (1)
// 	{
// 		str = get_next_line(0);
// 		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
// 			break ;
// 		write(fd, str, ft_strlen(str));
// 	}
// 	close(fd);
// 	return (filename);
// }

// void	do_redirection_in(char *val, int *fd, char is_heredoc)
// {
// 	char	*filename;

// 	if (is_heredoc)
// 		filename = create_heredoc_file(val);
// 	else
// 		filename = val;
// 	*fd = open(filename, O_RDONLY, 0644);
// 	if (fd < 0)
// 		print_error_n_exit("file open error");
// 	if (dup2(*fd, STDIN_FILENO) < 0)
// 		print_error_n_exit("dup2 error");
// }

// void	do_redirection_out(char *filename, int *fd, char is_append)
// {
// 	close(*fd);
// 	if (is_append)
// 		*fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (dup2(*fd, STDOUT_FILENO) < 0)
// 		print_error_n_exit("dup2 error");
// }