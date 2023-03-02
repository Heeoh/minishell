# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 13:36:04 by jkim3             #+#    #+#              #
#    Updated: 2023/03/02 16:40:07 by jkim3            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror
RLFLAGS = -lreadline -lhistory -L${READ_DIR}
INCLUDES = -I$(READ_HDRS)
READ_DIR = ${HOME}/.brew/opt/readline/lib
READ_HDRS	= ${HOME}/.brew/opt/readline/include

SRCS =  minishell.c \

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all :	$(NAME)

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(RLFLAGS) $(OBJS) -o $(NAME) 
			
clean   :	
			$(RM) $(OBJS)

fclean  :	clean
			$(RM) $(NAME)

re  :	fclean all

.PHONY  :	all clean fclean re