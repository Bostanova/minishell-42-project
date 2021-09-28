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

void	exec_last_cmd(t_cmds *cmd, int isbuildin, char ***env)
{
	pid_t	pid;

	// if (!isbuildin)
	// {
		pid = fork();
		if (pid == 0)
			execve(cmd->args[0], cmd->args, cmd->env);
		else
			waitpid(pid, NULL, 0);
	// }
	// else
	// 	exec_buildins(cmd, env);
}

void	write_outfile(t_cmds *cmd, int outfile_fd, int isbuildin, char ***env)
{
	pid_t	pid;

	// if (!isbuildin) {
		pid = fork();
		if (pid == 0)
		{
			dup2(outfile_fd, STDOUT_FILENO);
			close(outfile_fd);
			execve(cmd->args[0], cmd->args, cmd->env);
		}
		else
			waitpid(pid, NULL, 0);
	// }
	// else {
	// 	int save = dup(STDOUT_FILENO);
	// 	dup2(outfile_fd, STDOUT_FILENO);
	// 	close(outfile_fd);
	// 	exec_buildins(cmd, env);
	// 	dup2(STDOUT_FILENO, save);
	// }
}

void	execution(t_cmds *cmd, char ***env){
	char	**path;
	char	*tmp;
	int		in_out[2];
	int		isbuildin;

	tmp = NULL;
	path = NULL;
	while (cmd != NULL) {
		if (cmd->args[0]) {
			isbuildin = check_buildin(cmd->args[0]);
			if (!isbuildin) {
				path = get_path(*env);
				tmp = cmd->args[0];
				cmd->args[0] = test_path(path, cmd->args[0]);
			}
		}
		open_files(cmd, &in_out[0], &in_out[1]);
		if (cmd->outfile)
			write_outfile(cmd, in_out[1], isbuildin, env);
		else if (cmd->outfile == NULL && cmd->next == NULL)
			exec_last_cmd(cmd, isbuildin, env);
		else
			exec_cmd(cmd, isbuildin, env);		
		free_arr(path);
		if (tmp)
			free(tmp);
		cmd = cmd->next;
	}
}
