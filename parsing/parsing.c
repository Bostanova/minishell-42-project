/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:36:29 by eerika            #+#    #+#             */
/*   Updated: 2021/10/08 11:35:30 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	count_args(char *line, t_cmds *cmd, int *i)
{
	if ((!line[*i] || is_new_arg(line[*i])) && cmd->args)
	{
		if (cmd->args[cmd->count_args])
			cmd->count_args += 1;
	}
}

void check_grep(t_cmds *cmd)
{
	int i;

	i = 0;
	if (cmd)
	{
		while (cmd)
		{
			if (cmd->args[0] && !ft_strcmp(cmd->args[0], "grep"))
			{
				char **tmp = (char **)malloc(sizeof(char *) * (cmd->count_args + 2));
				while (cmd->args[i])
				{
					tmp[i] = ft_strdup(cmd->args[i]);
					i++;
				}
				tmp[i] = ft_strdup("-a");
				tmp[i + 1] = NULL;
				free_arr(cmd->args);
				cmd->args = tmp;
			}
			cmd = cmd->next;
		}
	}
}

int	parsing(t_cmds *cmd, char *line, char **env)
{
	int	*i;

	if (!line[0])
		return (1);
	i = (int *)malloc(sizeof(int));
	*i = 0;
	while (line[*i])
	{
		alloc_new_arg(cmd, line, i);
		if (ft_isspace(line[*i]))
			*i += 1;
		else if (line[*i] == '\'')
			parse_single_quotes(cmd, line, i, 0);
		else if (line[*i] == '\"')
			parse_double_quotes(cmd, line, i, 0);
		else if (line[*i] == '<' || line[*i] == '>')
		{
			if (parse_redirect(cmd, line, i))
			{
				free(i);
				return (1);
			}
		}
		else if (line[*i] == '$')
			parse_env(cmd, line, i, 0);
		else if (line[*i] == '|')
		{
			cmd->pipe = 1;
			cmd->next = init_cmd(env);
			cmd = cmd->next;
			*i += 1;
		}
		else
			parse_cmd(cmd, line, i);
		count_args(line, cmd, i);
	}
	free(i);
	check_grep(cmd);
	if (cmd->redir[0] == LESSLESS && !cmd->infile)
	{
		g_exit = 258;
		printf("minishell: syntax error near unexpected token '<'\n");
		return (1);
	}
	return (0);
}
