gcc -g *.c parsing/*.c builtins/*.c exec/*.c  libft/*.c -lreadline -o minishell

valgrind --trace-children=yes ./minishell


Fix it:

$? - порождает новый процесс, который не убивается,
	работает неправильно,
	утечка

echo $ a - не печатает 'a'

exit - din't close the programm

export - забыла сделать
export 'a'='b'
export a=6 b=8 c=9

env | grep SHLVL - Binary file (standard input) matches

unset "" a
unset a ""

cd /Users/eerika,  cd $HOME, pwd - переход не совершен

ls><abc
ls <> abc

