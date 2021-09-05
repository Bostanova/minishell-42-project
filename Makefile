DIR_HEADER	= ./includes/

SRC			= 	minishell.c \
				utils0.c \
				utils1.c \
				parsing.c 
				

OBJS		= $(SRC:.c=.o)

NAME		= minishell

RDLN_FLAG = -L/Users/eerika/.brew/Cellar/readline/8.1/lib/ -I/Users/eerika/.brew/Cellar/readline/8.1/include

GCC			= gcc -g
RM			= rm -f
CFLAGS		= -Wall -Wextra #-Werror 
NORM		= -R CheckForbiddenSourceHeader

%.o: %.c
			$(GCC) $(CFLAGS) -I $(DIR_HEADER) -c $< -o $@

$(NAME):	$(OBJS)
					$(GCC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L/Users/${USER}/.brew/Cellar/readline/8.1/lib/ -I/Users/${USER}/.brew/Cellar/readline/8.1/include-LLibft/ -LLibft/ -lft -L.

all:		$(NAME)

clean:
				$(RM) $(OBJS)

fclean:		clean
				make clean
				$(RM) $(NAME)

re:				fclean all

norme:
			norminette $(NORM) $(SRC)*.c $(DIR_HEADER)*.h

.PHONY:		all clean fclean re
