/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:25:27 by eerika            #+#    #+#             */
/*   Updated: 2021/10/12 12:07:41 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_mem(char **arr, char *str)
{
	if (arr)
		free_arr(arr);
	if (str)
		free(str);
}

int	get_pipe_number(t_cmds *cmd)
{
	int	res;

	res = 0;
	while (cmd->pipe)
	{
		res++;
		cmd = cmd->next;
	}
	return (res);
}

static void	sig_proc(t_cmds *cmd)
{
	int	status;
	int	count_pipe;
	int	j;

	count_pipe = get_pipe_number(cmd);
	j = 0;
	while (j <= count_pipe)
	{
		ignore_signals();
		waitpid(0, &status, WUNTRACED);
		if (WIFSIGNALED(status))
			child_signals(status);
		else
			if (count_pipe || WEXITSTATUS(status))
				g_exit = WEXITSTATUS(status);
		handle_signals();
		j++;
	}
}

void	execution(t_cmds *cmd, char ***env)
{
	char	**path;
	char	*tmp;
	int		in_out[2];
	int		isbuildin;
	int		stdin_initial;
	t_cmds	*head;

	head = cmd;
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
					free_mem(path, tmp);
					break ;
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
				write_outfile(cmd, in_out[1], stdin_initial);
			else if (cmd->outfile == NULL && cmd->next == NULL)
				exec_last_cmd(cmd, stdin_initial);
			else
				exec_cmd(cmd, isbuildin, env);
		}
		if (!isbuildin)
			free_mem(path, tmp);
		cmd = cmd->next;
	}
	sig_proc(head);
}
