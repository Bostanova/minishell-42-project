#include "../includes/minishell.h"

void	error_cmd_not_found(int nbr, char *err)
{
	g_exit = nbr;
	write(STDOUT_FILENO, "minishell: ", 12);
	write(STDOUT_FILENO, err, ft_strlen(err) + 1);
	write(STDOUT_FILENO, ": command not found\n", 21);
}

void	error_open_file(int nbr, char *err)
{
	g_exit = nbr;
	printf("minishell: %s: %s\n", err, strerror(errno));
}
