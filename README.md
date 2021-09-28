gcc -g *.c parsing/*.c builtins/*.c exec/*.c  libft/*.c -lreadline -o minishell

valgrind --trace-children=yes ./minishell
