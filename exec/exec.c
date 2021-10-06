#include "../includes/minishell.h"

void	exec_cmd(t_cmds *cmd, int isbuildin, char ***env)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0){
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!cmd->args[0])
			exit(EXIT_SUCCESS);
		else if (isbuildin) {
			go_to_buildin(cmd, env);
			exit(g_exit);
		}
		else
			if (execve(cmd->args[0], cmd->args, cmd->env) == -1)
			{
				error(1);
				exit(WTERMSIG(status));
			}
	} else {
		ignore_signals();
		waitpid(pid, &status, WUNTRACED);
		if (WIFSIGNALED(status))
			child_signals(status);
		else
			g_exit = WEXITSTATUS(status);
		handle_signals();
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	exec_last_cmd(t_cmds *cmd, char ***env, int stdin_initial)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0) {
		if (!cmd->args[0])
			exit(EXIT_SUCCESS);
		else {
			if (execve(cmd->args[0], cmd->args, cmd->env) == -1)
			{
				error(1);
				exit(WTERMSIG(status));
			}
		}
			
	}
	else {
		ignore_signals();
		waitpid(pid, &status, WUNTRACED);
		if (WIFSIGNALED(status))
			child_signals(status);
		else
			g_exit = WEXITSTATUS(status);
		handle_signals();
		if (stdin_initial != STDIN_FILENO)
			dup2(stdin_initial, STDIN_FILENO);
	}
}

void	write_outfile(t_cmds *cmd, int outfile_fd, char ***env, int stdin_initial)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		if (!cmd->args[0])
			exit(EXIT_SUCCESS);
		else {
			if (execve(cmd->args[0], cmd->args, cmd->env) == -1)
			{
				error(1);
				exit(WTERMSIG(status));
			}
		}
			
	}
	else {
		ignore_signals();
		waitpid(pid, &status, WUNTRACED);
		if (WIFSIGNALED(status))
			child_signals(status);
		else
			g_exit = WEXITSTATUS(status);
		handle_signals();
		if (stdin_initial != STDIN_FILENO)
			dup2(stdin_initial, STDIN_FILENO);
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
		if (isbuildin) {
			exec_buildins(cmd, in_out[1], env, stdin_initial);
		} else {
			if (cmd->outfile)
				write_outfile(cmd, in_out[1], env, stdin_initial);
			else if (cmd->outfile == NULL && cmd->next == NULL)
				exec_last_cmd(cmd, env, stdin_initial);
			else
				exec_cmd(cmd, isbuildin, env);
		}
		if (!isbuildin) {
			if (path)
				free_arr(path);
			if (tmp)
				free(tmp);
		}
		cmd = cmd->next;
	}
}
