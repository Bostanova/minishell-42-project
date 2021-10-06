#include "../includes/minishell.h"

static void	sigint(int sig)
{
	write(0, "\b\b  \b\b", 6);
	write(0, "\n", 1);
	write(1, PROMPT, ft_strlen(PROMPT));
	g_exit = 1;
}

static void	sigquit(int sig)
{
	write(0, "\b\b  \b\b", 6);
	g_exit = 0;
}

void	handle_signals(void)
{
	signal(SIGINT, sigint); 	/* ctrl-C print a new prompt on a newline	*/
	signal(SIGQUIT, sigquit); 	/* ctrl-\ do nothing						*/
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signals(int status)
{
	if (WTERMSIG(status) == 2)
		g_exit = 130;
	if (WTERMSIG(status) == 3)
	{
		write(1, "Quit: 3", 8);
		g_exit = 131;
	}
	write(1, "\n", 1);
}
