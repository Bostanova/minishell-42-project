#include "./includes/minishell.h"

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

static void	catch_exit_sig(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

int	main(int argc, char **argv, char **envp) {
	char	*line;
	char	**env;
	t_cmds	*cmd;

	(void)argc;
	(void)argv;
	g_exit = 0;
	env = NULL;
	env = get_array_of_env(envp);
	handle_signals();
	while (TRUE)
	{
		cmd = init_cmd(env);
		line = rl_gets();
		if (!line)
			catch_exit_sig();
		if (!(parsing(cmd, line, env)))
		{
			// print_cmd(cmd);
			execution(cmd, &env);
		}
		
		if (line)
			free(line);
		free_cmd(cmd);
		// system("leaks minishell");
	}
	clear_history();
	free_arr(env);

	// export MallocStackLogging=1  - in bash
	return (0);
}
