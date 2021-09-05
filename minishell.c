#include "./includes/minishell.h"
//check cmd structure
void print_arr(char **arr) {
	int i = 0;
	if (arr && arr[i]) {
		while (arr[i]) {
			printf("%s\n", arr[i]);
			i++;
		}
	}
}

void print_cmd(t_cmds *cmd) {
	print_arr(cmd->args);
	printf("cmd->count_args:%d\n", cmd->count_args);
	printf("cmd->redir[0]:	%d\n", cmd->redir[0]);
	printf("cmd->redir[1]:	%d\n", cmd->redir[1]);
	printf("cmd->pipe:	%d\n", cmd->pipe);
	printf("cmd->infile:	%s\n", cmd->infile);
	printf("cmd->outfile:	%s\n", cmd->outfile);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**env;
	t_cmds	*cmd;

	g_exit = 0;
	env = get_env(envp); 	//копия env (1)
	// while (TRUE)
	for (int i = 0; i < 2; i++)
	{
		cmd = init_cmd(env);
		line = rl_gets();		// (2)
		parsing(cmd, line);
		print_cmd(cmd);
		free(line);				// (2)
		free_cmd(cmd);
	}
	clear_history();			// (2)
	free_arr(env);				// (1)

	// system("leaks minishell");
	// export MallocStackLogging=1  - in bash
	return (0);
}
