NAME				:= 	minishell

CC					:= 	gcc
RM					:= 	rm -rf

OFLAGS				:=	-O2 -g#-fsanitize=address
CFLAGS				:= 	$(OFLAGS) -Wall #-Wextra #-Werror
NORM				:= 	-R CheckForbiddenSourceHeader

LIBFT_DIR			:= 	libft/
LIBFT				:= 	$(LIBFT_DIR)libft.a

INCLUDES			:= 	includes/
HEADER				:= 	$(INCLUDES)*.h

SRCS_DIR			:= 	parsing/
SRCS				:= 	$(SRCS_DIR)minishell.c\
						$(SRCS_DIR)utils0.c \
						$(SRCS_DIR)utils1.c \
						$(SRCS_DIR)parsing.c \
						$(SRCS_DIR)parse_cmd.c \
						$(SRCS_DIR)parse_quotes.c \
						$(SRCS_DIR)parse_env.c \
						$(SRCS_DIR)parse_redirect.c\

OBJS_DIR			:=	.objs/
OBJS				:=	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:%.c=%.o)))

all:				libft_make $(NAME)

$(NAME):			$(OBJS) $(LIBFT) Makefile
					$(CC) $(CFLAGS) -lreadline $(LIBFT) $(OBJS) -o $@

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c $(HEADER) | $(OBJS_DIR)
					$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
					mkdir -p $@

clean:
					$(RM) $(OBJS_DIR)

fclean:				clean
					$(RM) $(NAME)
					make fclean -C $(LIBFT_DIR)

re:					fclean all

libft_make:
					make -C $(LIBFT_DIR)

norme:
					norminette $(NORM) $(SRCS)*.c $(INCLUDES)*.h

.PHONY:				all clean fclean re libft_make
