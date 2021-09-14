#include "../includes/minishell.h"

void	error_export(int nbr, char *err) {
	g_exit = nbr;
	printf ("minishell: export: %s\n", err);
	exit(g_exit);
}