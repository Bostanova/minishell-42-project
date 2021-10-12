/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:32:33 by eerika            #+#    #+#             */
/*   Updated: 2021/10/11 19:27:37 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char	*rl_gets(void)
{
	char	*line;

	line = (char *) NULL;
	if (line)
	{
		free (line);
		line = (char *) NULL;
	}
	line = readline (PROMPT);
	if (line && *line)
		add_history (line);
	return (line);
}

t_cmds	*init_cmd(char **env)
{
	t_cmds	*cmd;

	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmd)
		ft_error(1);
	cmd->env = env;
	cmd->args = NULL;
	cmd->count_args = 0;
	cmd->redir[0] = 0;
	cmd->redir[1] = 0;
	cmd->pipe = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->isbuildin = 0;
	cmd->stdin_initial = STDIN_FILENO;
	cmd->stdout_initial = STDIN_FILENO;
	cmd->next = NULL;
	return (cmd);
}

char	**get_array_of_env(char **envp)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	while (envp[i])
		i++;
	res = (char **)malloc(sizeof(char *) * i + 1);
	res[i] = NULL;
	i = 0;
	while (envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		i++;
	}
	return (res);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
}

void	free_cmd(t_cmds *cmd)
{
	int		i;
	t_cmds	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		i = 0;
		if (cmd->args)
		{
			while (i < cmd->count_args)
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
		cmd = tmp;
	}
}
