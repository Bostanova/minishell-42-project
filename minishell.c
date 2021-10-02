#include "minishell.h"
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>

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

// void handler(pid_t pid) 
// {
// 	signal(SIGINT, SIG_IGN);
// 	int status;
// 	pid = getpid();
// 	printf("\nPid = %d\n", pid);

// 	pid = fork();
// 	waitpid(pid, &status, 0);

// 	if (!pid)
// 	{
// 		signal(SIGINT, print_lst);
// 		printf("\nChild process pid = %d\n", pid);	
// 		while (1)
// 			;		
// 		printf("\nChild process is end");	
// 	}
// 	else
// 	{
// 		printf("\nParent process pid = %d\n", pid);		
// 		signal(SIGINT, SIG_IGN);
// 	}
// }

int	main(int argc, char **argv, char **envp) {
	char	*line;
	t_env	*env;
	t_cmds	*cmd;


	pid_t pid;
	int status;
	printf("\nPid = %d\n", getpid());

	pid = fork();

	if (!pid)
	{
		// signal(SIGINT, ));
		printf("\nChild process pid = %d\n", pid);	
		for (int i = 0; i < 5; i++)
		{
			printf("This is a child process!");	
			sleep (1);
			printf("\b");	
		}
		printf("\nChild process is end\n");	
	}
	else
	{
		printf("\nParent process pid = %d\n", pid);		
		signal(SIGINT, SIG_IGN);
		// signal(SIGTERM, SIG_IGN);
		// signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		printf("->%d\n", WEXITSTATUS(status));
	}
	









	// char *p = getenv("PATH");

	// char **pp = ft_split(p, ':');
	// for (int i = 0; pp[i]; i++)
	// 	pp[i] = ft_join(pp[i], "/");
	// for (int i = 0; pp[i]; i++)
	// 		printf("%s\n", pp[i]);
	// free(p);
	// for (int i = 0; pp[i]; i++)
	// 	free(pp[i]);
	// exit(1);

	g_exit = 0;
	env = get_array_of_env(envp);
	// signals();
	for (int k = 0; k < 5; k++)  // change to "while (TRUE)"
	{
		cmd = init_cmd(env);
		line = rl_gets();
		parsing(cmd, line, env);
		printf("%s\n", line);	//remove later
		print_cmd(cmd);			//remove later
		// launch();

		free(line);
		free_cmd(cmd);
	}
	clear_history();
	free_env(env);

	// system("leaks minishell");
	// export MallocStackLogging=1  - in bash
	return (0);
}

