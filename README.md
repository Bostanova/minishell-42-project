gcc -g *.c parsing/*.c builtins/*.c exec/*.c  libft/*.c -lreadline -o minishell

valgrind --trace-children=yes ./minishell


Fix it:

коды выхода

env | grep HOME - Binary file (standard input) matches

unset "" a
unset a "" "" asd 123 "" 
unset a b c - segfault

<< EOF - segfault
<< EOF | wc -l

unset a