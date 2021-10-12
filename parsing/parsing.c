/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:36:29 by eerika            #+#    #+#             */
/*   Updated: 2021/10/11 18:53:40 by eerika           ###   ########.fr       */
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

static void	for_norm(t_cmds *cmd, char *line, int *i)
{
	if (ft_isspace(line[*i]))
		*i += 1;
	else if (line[*i] == '\'')
		parse_single_quotes(cmd, line, i, 0);
	else if (line[*i] == '\"')
		parse_double_quotes(cmd, line, i, 0);
	else
		parse_env(cmd, line, i, 0);
}

static void	parse_pipe(t_cmds *cmd, char **env, int *i)
{
	cmd->pipe = 1;
	cmd->next = init_cmd(env);
	*i += 1;
}

static int	main_parse_loop(t_cmds *cmd, int *i, char *line, char **env)
{
	while (line[*i])
	{
		alloc_new_arg(cmd, line, i);
		if (ft_isspace(line[*i]) || line[*i] == '\'' || line[*i] == '\"'
			|| line[*i] == '$')
			for_norm(cmd, line, i);
		else if (line[*i] == '<' || line[*i] == '>')
		{
			if (parse_redirect(cmd, line, i))
			{
				free(i);
				return (1);
			}
		}
		else if (line[*i] == '|')
		{
			parse_pipe(cmd, env, i);
			cmd = cmd->next;
		}
		else
			parse_cmd(cmd, line, i);
		count_args(line, cmd, i);
	}
	return (0);
}

int	parsing(t_cmds *cmd, char *line, char **env)
{
	int	*i;

	if (!line[0])
		return (1);
	i = (int *)malloc(sizeof(int));
	*i = 0;
	if ((main_parse_loop(cmd, i, line, env)))
		return (1);
	free(i);
	if (cmd->redir[0] == LESSLESS && !cmd->infile)
	{
		g_exit = 258;
		printf("minishell: syntax error near unexpected token '<'\n");
		return (1);
	}
	return (0);
}
