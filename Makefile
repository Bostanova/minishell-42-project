NAME				:= 	minishell

CC					:= 	gcc
RM					:= 	rm -rf

OFLAGS				:=	-O2 -g -lreadline -L/Users/${USER}/.brew/Cellar/readline/8.1.1/lib/ -I/Users/${USER}/.brew/Cellar/readline/8.1.1/include #-fsanitize=address
CFLAGS				:= 	$(OFLAGS) -Wall #-Wextra #-Werror
NORM				:= 	-R CheckForbiddenSourceHeader

LIBFT_DIR			:= 	libft/
LIBFT				:= 	$(LIBFT_DIR)libft.a

INCLUDES			:= 	includes/
HEADER				:= 	$(INCLUDES)*.h

SRCS_DIR			= 	parsing/ 
SRCS				:= 	minishell.c	utils0.c \
									utils1.c \
									parsing.c \
									parse_cmd.c \
									parse_quotes.c \
									parse_env.c \
									parse_redirect.c\
									error_pars.c\



OBJS_DIR			:=	.objs/
OBJS				:=	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:%.c=%.o)))

VPATH				=	$(SRCS_DIR) exec/ builtins/

all:				libft_make $(NAME)

$(NAME):			$(OBJS_DIR) $(OBJS) $(LIBFT) Makefile
					$(CC) $(CFLAGS) -lreadline $(LIBFT) $(OBJS) -o $@

$(OBJS_DIR)%.o:		%.c $(HEADER)
					$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
					@mkdir -p $@

clean:
					$(RM) $(OBJS_DIR)

fclean:				clean
					$(RM) $(NAME)
					make fclean -C $(LIBFT_DIR)

re:					fclean all

libft_make:
					@make -C $(LIBFT_DIR)

norme:
					norminette $(NORM) $(SRCS)*.c $(INCLUDES)*.h
gitpush_e:
					git branch eerika
					git add .
					git commit -m "New edition"
					git push origin eerika
gitpush_f:
					git status
					git add .
					git status
					git commit -m "New edition"
					git push origin feschall


.PHONY:				all clean fclean re libft_make