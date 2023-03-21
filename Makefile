# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkim3 <jkim3@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 13:36:04 by jkim3             #+#    #+#              #
#    Updated: 2023/03/21 17:23:42 by jkim3            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------- NAME ------------------------------------ #

NAME = minishell

# ------------------------------- DIRECTORIES -------------------------------- #

LIBFT_DIR	= library/libft/
GNL_DIR		= library/get_next_line/
HDRS_DIR	= headers/
SRCS_DIR	= sources/
OBJS_DIR	= objects/
READ_DIR 	= ${HOME}/.brew/opt/readline/lib
READ_HDRS	= ${HOME}/.brew/opt/readline/include

# ---------------------------------- FILES ----------------------------------- #

LIBS = $(LIBFT_DIR)libft.a $(GNL_DIR)libgnl.a
INCLUDE = -I $(HDRS_DIR) -I $(LIBFT_DIR) -I $(GNL_DIR)
SRCS = $(wildcard $(SRCS_DIR)*.c)
OBJS += $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

# -------------------------------- COMPILATE --------------------------------- #

CFLAGS = -Wall -Wextra -Werror 
# -g -fsanitize=address
RLFLAGS = -lreadline -lhistory -L${READ_DIR}
RM		= rm -rf
MD		= mkdir -p 
#AR		= ar -rcs

# --------------------------------- RULES ------------------------------------ #

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -g -c $< -o $@

all :	
		make bonus -C $(LIBFT_DIR)
		make -C $(GNL_DIR)
		make $(NAME)
		

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(RLFLAGS) $(OBJS) $(LIBS) -g -o $(NAME) 
			
clean   :	
			make clean -C $(LIBFT_DIR)
			make clean -C $(GNL_DIR)
			$(RM) $(OBJS_DIR)

fclean  :	clean
			$(RM) $(LIBS) $(NAME) 

re  :	fclean all

.PHONY  :	all clean fclean re
