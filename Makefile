#		gcc -g *.c libft/*.c -lreadline -o minishell
#		gcc -g -fsanitize=address *.c libft/*.c -lreadline -o minishell
DIR_HEADER	= ./includes/

SRC			= 	minishell.c \
				utils0.c \
				utils1.c \
				parsing.c \
				parse_cmd.c \
				parse_quotes.c \
				parse_env.c 
				

OBJS		= $(SRC:.c=.o)

NAME		= minishell

GCC			= gcc -g
CFLAGS		= -Wall -Wextra #-Werror 

NORM		= -R CheckForbiddenSourceHeader

%.o: %.c
			$(GCC) $(CFLAGS) -I $(DIR_HEADER) -c $< -o $@

$(NAME):	$(OBJS)
					$(GCC) $(CFLAGS) $(OBJS) -lreadline libft/libft.a -o $(NAME) 

all:		$(NAME)

clean:
				rm -f $(OBJS)

fclean:		clean
				make clean
				rm -f $(NAME)

re:				fclean all

norme:
			norminette $(NORM) $(SRC)*.c $(DIR_HEADER)*.h

.PHONY:		all clean fclean re
