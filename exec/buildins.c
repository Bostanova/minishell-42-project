#include "../includes/minishell.h"

int	check_buildin(char *cmd)
{
	if (!strcmp(cmd, "cd") || !strcmp(cmd, "echo")\
		|| !strcmp(cmd, "Echo") || !strcmp(cmd, "exit")\
		|| !strcmp(cmd, "export") || !strcmp(cmd, "pwd")\
		|| !strcmp(cmd, "unset") || !strcmp(cmd, "env") )
		return (1);
	return (0);
}

void	go_to_buildin(t_cmds *cmd, char ***env)
{
	if (!strcmp(cmd->args[0], "cd"))
		cd_cmd(cmd, env);
	else if (!strcmp(cmd->args[0], "echo") || !strcmp(cmd->args[0], "Echo"))
		echo_cmd(cmd);
	else if (!strcmp(cmd->args[0], "exit"))
		exit_cmd(cmd);
	else if (!strcmp(cmd->args[0], "env"))
		env_cmd(cmd);
	else if (!strcmp(cmd->args[0], "pwd"))
		pwd_cmd();
	else if (!strcmp(cmd->args[0], "unset"))
		unset_cmd(cmd, env);
	else
		export_cmd(cmd, env);
}

void	exec_buildins_in_middle_of_line(t_cmds *cmd, char ***env, int stdout_initial) {
	int		fd[2];

	pipe(fd);
	// close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	// close(fd[1]);
	go_to_buildin(cmd, env);
	dup2(fd[0], STDIN_FILENO);	
	dup2(stdout_initial, STDOUT_FILENO);
}

void	exec_buildins(t_cmds *cmd, int outfile_fd, char ***env, int stdin_initial) {
	int	stdout_initial;

	stdout_initial = dup(STDOUT_FILENO);
	if (cmd->outfile) {
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		go_to_buildin(cmd, env);
		dup2(stdout_initial, STDOUT_FILENO);
		close(stdout_initial);
		if (stdin_initial != STDIN_FILENO)
			dup2(stdin_initial, STDIN_FILENO);
	}
	else if (cmd->outfile == NULL && cmd->next == NULL)
		go_to_buildin(cmd, env);
		dup2(stdout_initial, STDOUT_FILENO);
		close(stdout_initial);
		if (stdin_initial != STDIN_FILENO)
			dup2(stdin_initial, STDIN_FILENO);
	else
		exec_buildins_in_middle_of_line(cmd, env, stdout_initial);
}
