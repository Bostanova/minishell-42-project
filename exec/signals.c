#include "../includes/minishell.h"

static void	sigint(int sig)
{
	// printf("\033[2D");
	printf("\n"); 
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay();
	g_exit = 1;
}

static void	sigquit(int sig)
{
	// write(1, "\b\b \b\b", 6);
	// printf("\033[2D");
    rl_on_new_line();
    rl_redisplay();
	g_exit = 0;
}

void	handle_signals(void)
{
	signal(SIGQUIT, sigquit); 	/* ctrl-\ do nothing	*/
	signal(SIGINT, sigint); 	/* ctrl-C print a new prompt on a newline	*/
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
