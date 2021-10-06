/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:45:51 by eerika            #+#    #+#             */
/*   Updated: 2021/10/06 10:44:41 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_with_value(t_cmds *cmd)
{
	unsigned long	i;

	i = 0;
	if (cmd->args[1][i] == '-' && !cmd->args[1][i + 1])
		error_exit(255, cmd->args[1]);
	if (cmd->args[1][i] == '-' || cmd->args[1][i] == '+')
		i++;
	while (cmd->args[1][i])
	{
		if (!(ft_isdigit(cmd->args[1][i])))
			error_exit(255, cmd->args[1]);
		i++;
	}
	exit(ft_atoi(cmd->args[1]) % 256);
}

void	exit_cmd(t_cmds *cmd)
{
	if (cmd->count_args == 1)
	{
		write(STDOUT_FILENO, "exit\n", 6);
		g_exit = 0;
		exit(g_exit);
	}
	else if (cmd->count_args == 2)
		exit_with_value(cmd);
	else
		error_exit(1, NULL);
}
