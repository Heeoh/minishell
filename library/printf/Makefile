
# ---------------------------------- NAME ------------------------------------ #

NAME = libftprintf.a

# ------------------------------- DIRECTORIES -------------------------------- #

HDRS_DIR = headers/
SRCS_DIR = sources/
OBJS_DIR = objects/

# ---------------------------------- FILES ----------------------------------- #

SRCS		= $(wildcard $(SRCS_DIR)*_utils.c)
SRCS_UTILS	= $(wildcard $(SRCS_DIR)utils/*.c)
SRCS_MAN	= ft_printf_man.c
SRCS_BONUS	= ft_printf_bonus.c

OBJS		+= $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))
OBJS_UTILS	+= $(addprefix $(OBJS_DIR)utils/, $(notdir $(SRCS_UTILS:.c=.o)))
OBJS_MAN	+= $(addprefix $(OBJS_DIR), $(notdir $(SRCS_MAN:.c=.o)))
OBJS_BONUS	+= $(addprefix $(OBJS_DIR), $(notdir $(SRCS_BONUS:.c=.o)))

ifdef ADD_BONUS
	OBJECTS = $(OBJS) $(OBJS_UTILS) $(OBJS_BONUS)
else
	OBJECTS = $(OBJS) $(OBJS_UTILS) $(OBJS_MAN) 
endif

# -------------------------------- COMPILATE --------------------------------- #

CC		= cc
CFLAGS	= -Wall -Werror -Wextra
AR		= ar -rcs
MD		= mkdir -p
RM		= rm -rf

# --------------------------------- RULES ------------------------------------ #

$(OBJS_DIR)%o : $(SRCS_DIR)%c
		$(MD) $(dir $@)
		$(CC) $(CFLAGS) -I $(HDRS_DIR) -c $< -o $@

$(NAME) : $(OBJECTS)
		$(AR) $@ $(OBJECTS)

bonus :
		make ADD_BONUS=1 
		make all

all : $(NAME)

clean :
		$(RM) $(OBJECTS) $(OBJS_DIR)

fclean : clean
		$(RM) $(NAME)

re :
	make fclean 
	make all

.PHONY : all clean fclean re bonus
