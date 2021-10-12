/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:35:16 by eerika            #+#    #+#             */
/*   Updated: 2021/10/11 15:36:10 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static void	catch_exit_sig(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "\033[Aexit\n", 9);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**env;
	t_cmds	*cmd;

	(void)argc;
	(void)argv;
	g_exit = 0;
	env = NULL;
	env = get_array_of_env(envp);
	handle_signals();
	while (TRUE)
	{
		cmd = init_cmd(env);
		line = rl_gets();
		if (!line)
			catch_exit_sig();
		if (!(parsing(cmd, line, env)))
			execution(cmd, &env);
		if (line)
			free(line);
		free_cmd(cmd);
	}
	clear_history();
	free_arr(env);
	return (0);
}
