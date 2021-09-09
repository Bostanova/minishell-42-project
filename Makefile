#		gcc -g parsing/*.c  *.c libft/*.c -lreadline -o minishell
#		gcc -g -fsanitize=address *.c libft/*.c -lreadline -o minishell
DIR_HEADER	= ./includes/

SRC			= 	minishell.c \
				parsing/utils0.c \
				parsing/utils1.c \
				parsing/parsing.c \
				parsing/parse_cmd.c \
				parsing/parse_quotes.c \
				parsing/parse_env.c \
				parsing/parse_redirect.c
				

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
