CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libgnl.a

OBJS_DIR = objects/

SRCS = $(wildcard *.c)

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

$(OBJS_DIR)%o : %c
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
		ar -crs $@ $(OBJS)

all : $(NAME)

clean :
		rm -rf $(OBJS) $(OBJS_DIR)

fclean : clean
		rm -rf $(NAME)
re :
	make fclean 
	make all

.PHONY : all clean fclean re
