NAME				:= 	minishell

CC					:= 	gcc
RM					:= 	rm -rf

RFLAGS				:=	-lreadline -L/Users/${USER}/.brew/Cellar/readline/8.1.1/lib/ -I/Users/${USER}/.brew/Cellar/readline/8.1.1/include
OFLAGS				:=	-O2 -g #-fsanitize=address
CFLAGS				:= 	$(OFLAGS) -Wall -Wextra -Werror
NORM				:= 	-R CheckForbiddenSourceHeader

LIBFT_DIR			:= 	libft/
LIBFT				:= 	$(LIBFT_DIR)libft.a

INCLUDES			:= 	includes/
HEADER				:= 	$(INCLUDES)*.h

VPATH				=	$(SRCS_DIRS)
SRCS_DIRS			=	builtins/	exec/	parsing/
SRCS				:= 	minishell.c	\
						cd.c	echo.c	env.c	exit.c	export.c	pwd.c	unset.c	\
						buildins.c	find_path_to_binary.c	signals_heredoc.c	error_exec.c	in_out.c	exec.c	signals.c	exec_cmd.c\
						error_pars.c	parse_env.c	parse_redirect.c	utils0.c	parse_cmd.c	parse_quotes.c	parsing.c	utils1.c

OBJS_DIR			:=	.objs/
OBJS				:=	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:%.c=%.o)))

all:				libft_make $(NAME)


$(NAME):			$(OBJS_DIR) $(OBJS) $(LIBFT) Makefile
					$(CC) $(CFLAGS) $(RFLAGS) $(LIBFT) $(OBJS) -o $@

$(OBJS_DIR)%.o:		%.c $(HEADER)
					$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
					@mkdir -p $@
clean:
					make clean -C $(LIBFT_DIR)
					$(RM) $(OBJS_DIR)
					
fclean:				clean
					make fclean -C $(LIBFT_DIR)
					$(RM) $(NAME)
					$(RM) .gitpush

re:					fclean all

libft_make:
					@make -C $(LIBFT_DIR)

norme:
					norminette $(NORM) $(SRCS)*.c $(INCLUDES)*.h

gitpush:
					sh .gitpush || {									\
					echo '#!/bin/sh' > .gitpush;						\
					echo 'git status' >> .gitpush;						\
					echo 'git add .' >> .gitpush;						\
					echo 'git status' >> .gitpush;						\
					echo 'echo Enter commits name: ' >> .gitpush;		\
					echo 'read commits_name' >> .gitpush;				\
					echo 'git commit -m "$$commits_name"' >> .gitpush;	\
					echo 'git push origin $${USER}' >> .gitpush;}
# sh .gitpush;}

.PHONY:				all clean fclean re libft_make
