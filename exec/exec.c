#include "../includes/minishell.h"

void	exec_cmd(t_cmds *cmd, int isbuildin, char ***env)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	ignore_signals();
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
		else
			if (execve(cmd->args[0], cmd->args, cmd->env) == -1)
			{
				error(1);
				exit(WTERMSIG(status));
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

void foo(char **arr, char *str)
{
	if (arr)
		free_arr(arr);
	if (str)
		free(str);
}

int get_pipe_number(t_cmds *cmd)
{
	int res;

	res = 0;
	while (cmd->pipe)
	{
		res++;
		cmd = cmd->next;
	}
	return(res);
}

void	execution(t_cmds *cmd, char ***env){
	char	**path;
	char	*tmp;
	int		in_out[2];
	int		isbuildin;
	int		stdin_initial;
	int		status;
	t_cmds *tmp2 = cmd;

	stdin_initial = dup(STDIN_FILENO);
	tmp = NULL;
	path = NULL;
	isbuildin = 0;
	while (cmd != NULL) 
	{
		if (cmd->args[0]) 
		{
			isbuildin = check_buildin(cmd->args[0]);
			if (!isbuildin && (access(cmd->args[0], X_OK))) 
			{
				path = get_path(*env);
				if (!path)
				{
					error_cmd_not_found(cmd->args[0]);
					foo(path, tmp);
					break;
				}
				tmp = cmd->args[0];
				cmd->args[0] = test_path(path, cmd->args[0]);
			}
		}
		open_files(cmd, &in_out[0], &in_out[1]);
		if (isbuildin)
			exec_buildins(cmd, in_out[1], env, stdin_initial);
		else
		{
			if (cmd->outfile)
				write_outfile(cmd, in_out[1], env, stdin_initial);
			else if (cmd->outfile == NULL && cmd->next == NULL)
				exec_last_cmd(cmd, env, stdin_initial);			//fork
			else
				exec_cmd(cmd, isbuildin, env);					//fork
		}
		if (!isbuildin)
			foo(path, tmp);
		cmd = cmd->next;
	}
	int count_pipe = get_pipe_number(tmp2);
	for (int f = 0; f <= count_pipe; f++)
    {
		ignore_signals();
		waitpid(0, &status, WUNTRACED);
		if (WIFSIGNALED(status))
			child_signals(status);
		else
			if (count_pipe || WEXITSTATUS(status))
				g_exit = WEXITSTATUS(status);
		handle_signals();
    }
}
