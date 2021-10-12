/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:03:26 by eerika            #+#    #+#             */
/*   Updated: 2021/10/11 17:13:51 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit = 1;
}

static void	sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b", 4);
	g_exit = 0;
}

void	handle_signals(void)
{
	signal(SIGQUIT, sigquit);
	signal(SIGINT, sigint);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signals(int status)
{
	if (WTERMSIG(status) == 2)
	{
		g_exit = 130;
		write(1, "\n", 1);
	}
	if (WTERMSIG(status) == 3)
	{
		write(1, " \bQuit: 3\n", 10);
		g_exit = 131;
	}
}
