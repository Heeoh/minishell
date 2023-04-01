# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heson <heson@Student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 13:36:04 by jkim3             #+#    #+#              #
#    Updated: 2023/04/01 21:49:56 by heson            ###   ########.fr        #
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
INCLUDE = -I $(HDRS_DIR) -I $(LIBFT_DIR) -I $(GNL_DIR) -I ${READ_HDRS}
SRCS = $(wildcard $(SRCS_DIR)*.c)
SRCS += $(wildcard $(SRCS_DIR)built_in/*.c)
SRCS += $(wildcard $(SRCS_DIR)env/*.c)
SRCS += $(wildcard $(SRCS_DIR)exe/*.c)
SRCS += $(wildcard $(SRCS_DIR)parsing/*.c)
OBJS += $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

# -------------------------------- COMPILATE --------------------------------- #

CFLAGS = -Wall -Wextra -Werror 
# -g -fsanitize=address
RLFLAGS = -lreadline -lhistory -L${READ_DIR}
RM		= rm -rf
MD		= mkdir -p 

# --------------------------------- RULES ------------------------------------ #

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	$(MD) $(dir $@)
	gcc $(CFLAGS) $(INCLUDE) -g -c $< -o $@

all :	
		make bonus -C $(LIBFT_DIR)
		make -C $(GNL_DIR)
		make $(NAME)
		

$(NAME) :	$(OBJS)
			gcc $(CFLAGS) $(RLFLAGS) $(OBJS) $(LIBS) -g -o $(NAME) 
			
clean   :	
			make clean -C $(LIBFT_DIR)
			make clean -C $(GNL_DIR)
			$(RM) $(OBJS_DIR)

fclean  :	clean
			$(RM) $(LIBS) $(NAME) 

re  :	fclean all

.PHONY  :	all clean fclean re
