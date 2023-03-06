CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

OBJS_DIR = objects/

SRCS_MAN = $(wildcard *_man.c)
SRCS_BONUS = $(wildcard *_bonus.c)

OBJS_MAN = $(addprefix $(OBJS_DIR), $(SRCS_MAN:.c=.o))
OBJS_BONUS = $(addprefix $(OBJS_DIR), $(SRCS_BONUS:.c=.o))

ifdef ADD_BONUS
		OBJECTS = $(OBJS_MAN) $(OBJS_BONUS)
else
		OBJECTS = $(OBJS_MAN)
endif

$(OBJS_DIR)%o : %c
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJECTS)
		ar -crs $@ $(OBJECTS)

bonus :
		make ADD_BONUS=1 
		make all

all : $(NAME)

clean :
		rm -rf $(OBJECTS) $(OBJS_DIR)

fclean : clean
		rm -rf $(NAME)
re :
	make fclean 
	make all

.PHONY : all clean fclean re bonus
