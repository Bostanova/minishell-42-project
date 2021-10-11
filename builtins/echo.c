/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:44:36 by eerika            #+#    #+#             */
/*   Updated: 2021/10/11 16:33:03 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_echo(char **args)
{
	int	i;

	i = 1;
	if (!(ft_strcmp(args[1], "-n")))
		i++;
	while (args[i] && args[i + 1])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
}

void	echo_cmd(t_cmds *cmd)
{
	if (cmd->args[1])
		print_echo(cmd->args);
	else
		write(STDOUT_FILENO, "\n", 1);
	if (cmd->args[1])
		if (ft_strcmp(cmd->args[1], "-n"))
			write(STDOUT_FILENO, "\n", 1);
	g_exit = 0;
}
