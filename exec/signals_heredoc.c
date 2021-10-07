#include "../includes/minishell.h"

static void	sigint_heredoc(int sig)
{
	write(0, "\b\b  \b\b", 6);
	g_exit = 1;
	exit(1);
}

static void	sigquit_heredoc(int sig)
{
	write(0, "\b\b  \b\b", 6);
	g_exit = 0;
}

void	handle_signals_heredoc(void)
{
	signal(SIGQUIT, sigquit_heredoc); 	/* ctrl-\ do nothing	*/
	signal(SIGINT, sigint_heredoc); 	/* ctrl-C print a new prompt on a newline	*/
}