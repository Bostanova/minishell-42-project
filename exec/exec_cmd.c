/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:31:07 by eerika            #+#    #+#             */
/*   Updated: 2021/10/11 17:50:12 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	go_to_execve(t_cmds *cmd)
{
	int		status;

	execve(cmd->args[0], cmd->args, cmd->env);
	error(1);
	exit(WTERMSIG(status));
}

static void	parent_proc(int *fd_in, int *fd_out)
{
	handle_signals();
	close(*fd_out);
	dup2(*fd_in, STDIN_FILENO);
	close(*fd_in);
}

void	exec_cmd(t_cmds *cmd, int isbuildin, char ***env)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	ignore_signals();
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!cmd->args[0])
			exit(EXIT_SUCCESS);
		else if (isbuildin)
		{
			go_to_buildin(cmd, env);
			exit(g_exit);
		}
		else
			go_to_execve(cmd);
	}
	else
		parent_proc(&fd[0], &fd[1]);
}

void	exec_last_cmd(t_cmds *cmd, int stdin_initial)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!cmd->args[0])
			exit(EXIT_SUCCESS);
		else
			go_to_execve(cmd);
	}
	else
		if (stdin_initial != STDIN_FILENO)
			dup2(stdin_initial, STDIN_FILENO);
}

void	write_outfile(t_cmds *cmd, int outfile_fd, int stdin_initial)
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
			go_to_execve(cmd);
	}
	else
	{
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
