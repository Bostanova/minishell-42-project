/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:45:45 by eerika            #+#    #+#             */
/*   Updated: 2021/10/05 19:35:04 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_cmd(t_cmds *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1])
	{
		g_exit = 127;
		write(1, "minishell: ", 12);
		write(1, cmd->args[1], ft_strlen(cmd->args[1]));
		write(1, ": No such file or directory", 28);
	}
	while (cmd->env[i])
	{
		write(STDOUT_FILENO, cmd->env[i], ft_strlen(cmd->env[i]) + 1);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
