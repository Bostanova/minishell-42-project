#include "../includes/minishell.h"

void	exec_cmd(t_cmds *cmd, int isbuildin, char ***env)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (isbuildin) {
			exec_buildins(cmd, env);
			exit(EXIT_SUCCESS);
		}
		else if (!cmd->args[0])
			exit(EXIT_SUCCESS);
		else
			execve(cmd->args[0], cmd->args, cmd->env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	exec_last_cmd(t_cmds *cmd, int isbuildin, char ***env, int stdin_initial)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0) {
		if (isbuildin){
			exec_buildins(cmd, env);
			exit(EXIT_SUCCESS);
		}
		else if (!cmd->args[0])
			exit(EXIT_SUCCESS);
		else
			execve(cmd->args[0], cmd->args, cmd->env);
	}	
	else {
		waitpid(pid, NULL, 0);
		if (stdin_initial != STDIN_FILENO) {
			dup2(stdin_initial, STDIN_FILENO);
			close(stdin_initial);
		}	
	}
}

void	write_outfile(t_cmds *cmd, int outfile_fd, int isbuildin, char ***env, int stdin_initial)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		if (isbuildin) {
			exec_buildins(cmd, env);
			exit(EXIT_SUCCESS);
		}
		else if (!cmd->args[0])
			exit(EXIT_SUCCESS);
		else
			execve(cmd->args[0], cmd->args, cmd->env);
	}
	else {
		waitpid(pid, NULL, 0);
		if (stdin_initial != STDIN_FILENO) {
			dup2(stdin_initial, STDIN_FILENO);
			close(stdin_initial);
		}
	}
}

void	execution(t_cmds *cmd, char ***env){
	char	**path;
	char	*tmp;
	int		in_out[2];
	int		isbuildin;
	int		stdin_initial;

	stdin_initial = dup(STDIN_FILENO);
	tmp = NULL;
	path = NULL;
	while (cmd != NULL) {
		if (cmd->args[0]) {
			isbuildin = check_buildin(cmd->args[0]);
			if (!isbuildin && (access(cmd->args[0], X_OK))) {
				path = get_path(*env);
				tmp = cmd->args[0];
				cmd->args[0] = test_path(path, cmd->args[0]);
			}
		}
		open_files(cmd, &in_out[0], &in_out[1]);
			if (cmd->outfile)
				write_outfile(cmd, in_out[1], isbuildin, env, stdin_initial);
			else if (cmd->outfile == NULL && cmd->next == NULL)
				exec_last_cmd(cmd, isbuildin, env, stdin_initial);
			else
				exec_cmd(cmd, isbuildin, env);
		free_arr(path);
		if (tmp)
			free(tmp);
		cmd = cmd->next;
	}
}
