brew install readline

gcc -g *.c parsing/*.c builtins/*.c exec/*.c  libft/*.c -lreadline -L/Users/eerika/.brew/Cellar/readline/8.1.1/lib/ -I/Users/eerika/.brew/Cellar/readline/8.1.1/include -o minishell

valgrind --trace-children=yes ./minishell

lsof -c minishell

Fix it:

unset ""

echo -n -n -n test tout
echo "$TEST$TEST=lol$TEST"
echo $TEST$TEST=lol$TEST""lol
echo "$=TEST"
echo "$"
echo "$1TEST"

export TE+S=T=""
export TEST+=LOL

cd . - seg fault

head -c 2000000 /dev/zero > big_file
cat big_file | ls

cat < infile (infile doesn't exist)
cat > ls < ls


Чек-лист
сигналы и коды


//for checking cmd structure, remove later
void print_arr(char **arr) {
	int i = 0;
	if (arr && arr[i]) {
		while (arr[i]) {
			printf("%s\n", arr[i]);
			i++;
		}
	}
}
//for checking cmd structure, remove later
void print_cmd(t_cmds *cmd) {
	int i;
	t_cmds *tmp;
	while (cmd != NULL) {
		tmp = cmd;
		i = 0;
		if (cmd->args) {
			while (cmd->args[i]) {
				printf("args[%d] = %s\n", i, cmd->args[i]);
				i++;
			}
		}
		printf("cmd->count_args:%d\n", cmd->count_args);
		printf("cmd->redir[0]:	%d\n", cmd->redir[0]);
		printf("cmd->redir[1]:	%d\n", cmd->redir[1]);
		printf("cmd->pipe:	%d\n", cmd->pipe);
		printf("cmd->infile:	%s\n", cmd->infile);
		printf("cmd->outfile:	%s\n", cmd->outfile);
		if (cmd->next == NULL)
			printf("cmd->next = null\n");
		else
			printf("cmd->next != null\n");
		cmd = tmp->next;
	}
}

// system("leaks minishell");
// export MallocStackLogging=1  - in bash
