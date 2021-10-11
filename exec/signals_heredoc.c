/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:58:22 by eerika            #+#    #+#             */
/*   Updated: 2021/10/11 15:58:23 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sigint_heredoc(int sig)
{
	write(0, "\b\b  \b\b", 6);
	g_exit = 130;
	exit(130);
}

static void	sigquit_heredoc(int sig)
{
	write(0, "\b\b  \b\b", 6);
	g_exit = 0;
}

void	handle_signals_heredoc(void)
{
	signal(SIGQUIT, sigquit_heredoc);
	signal(SIGINT, sigint_heredoc);
}
