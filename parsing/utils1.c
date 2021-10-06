/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:51:55 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 18:51:57 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	stop_char(char c)
{
	if ((c >= '!' && c <= ';') || c == '=')
		return (1);
	else if (c >= '?' && c <= '{')
		return (1);
	else if (c >= '}' && c <= '~')
		return (1);
	return (0);
}

void	alloc_new_arg(t_cmds *cmd, char *line, int *i)
{
	if (*i == 0 || (cmd->count_args == 0 && !cmd->args))
		cmd->args = global_alloc(cmd->args, 1);
	else if (ft_isspace(line[*i - 1]) && stop_char(line[*i]))
		cmd->args = global_alloc(cmd->args, (1 + cmd->count_args));
	else if (line[*i] == '<')
	{
		if (cmd->infile)
		{
			free(cmd->infile);
			cmd->infile = NULL;
		}
	}
	else if (line[*i] == '>')
	{
		if (cmd->outfile)
		{
			free(cmd->outfile);
			cmd->outfile = NULL;
		}
	}
}
