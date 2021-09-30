gcc -g *.c parsing/*.c builtins/*.c exec/*.c  libft/*.c -lreadline -o minishell

valgrind --trace-children=yes ./minishell

lsof -c minishell


Fix it:

коды выхода

env | grep HOME - Binary file (standard input) matches

unset "" a
unset a "" "" asd 123 "" 

<< EOF - segfault
<< EOF | wc -l