NAME			= minishell
CC				= gcc
RM				= rm -rf

LEACS			= #-fsanitize=address
CFLAGS			= $(LEACS) -lreadline #-Wall -Wextra #-Werror -O2 -g
NORM			= -R CheckForbiddenSourceHeader

LIBFT_DIR		= libft/
LIBFT			= $(LIBFT_DIR)libft.a

INCLUDES		= includes/
HEADER			= $(wildcard $(INCLUDES)*.h)

SRC_DIR			= parsing/
BUILT_DIR		= buitins/
SRCS			= minishell.c	$(SRC_DIR)utils0.c \
								$(SRC_DIR)utils1.c \
								$(SRC_DIR)parsing.c \
								$(SRC_DIR)parse_cmd.c \
								$(SRC_DIR)parse_quotes.c \
								$(SRC_DIR)parse_env.c \
								$(SRC_DIR)parse_redirect.c
								$(BUILT_DIR)cd.c \
								$(BUILT_DIR)pwd.c \
								$(BUILT_DIR)env.c

OBJ_DIR			= .objs/
OBJS			= $(addprefix $(OBJ_DIR), $(notdir $(SRCS:%.c=%.o)))

all:			libft_make $(NAME)

$(NAME):		$(OBJS) Makefile 
				$(CC) $(CFLAGS)  $(LIBFT) $(OBJS) -o $@

$(OBJ_DIR)%.o:	$(SRCS) $(LIBFT) $(HEADER) | $(OBJ_DIR)
				$(CC) -c $(CFLAGS) -I$(HEADER) $< -o $@

$(OBJ_DIR):
				mkdir -p $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(OBJ_DIR)
				-make fclean -C $(LIBFT_DIR)

re:				fclean all

libft_make:
				-make -C $(LIBFT_DIR)

norme:
				norminette $(NORM) $(SRCS)*.c $(INCLUDES)*.h

.PHONY:			all clean fclean re libft_make
