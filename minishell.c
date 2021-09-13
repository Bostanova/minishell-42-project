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
		cmd = tmp->next;
	}
}

void print_lst(t_env *env) {
	t_env *head = env;

	while (env) {
		printf("%s=%s\n", env->name, env->data);
		env = env->next;
	}
}

int	main(int argc, char **argv, char **envp) {
	char	*line;
	t_env	*env;
	t_cmds	*cmd;

	g_exit = 0;
	env = get_array_of_env(envp);
	for (int k = 0; k < 5; k++)  // change to "while (TRUE)"
	{
		cmd = init_cmd(env);
		line = rl_gets();
		parsing(cmd, line, env);
		printf("%s\n", line);	//remove later
		print_cmd(cmd);			//remove later
		}
		free(line);
		free_cmd(cmd);
	}
	clear_history();
	free_env(env);


	// system("leaks minishell");
	// export MallocStackLogging=1  - in bash
	return (0);
}
