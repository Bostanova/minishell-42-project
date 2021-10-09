brew install readline

gcc -g *.c parsing/*.c builtins/*.c exec/*.c  libft/*.c -lreadline -L/Users/eerika/.brew/Cellar/readline/8.1.1/lib/ -I/Users/eerika/.brew/Cellar/readline/8.1.1/include -o minishell

valgrind --trace-children=yes ./minishell

lsof -c minishell

Fix it:

unset ""

env | grep HOME

параллельное выполнение
