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

static void	error_errno(void)
{
	char	*err;
	
	err = strerror(errno);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
}

void	error(int error)
{
	if (error == 0)
		error_errno();
	else if (error == 1)
	{
		g_exit = 126;
		error_errno();
	}
	else if (error == 2)
		ft_putendl_fd("minishell: Allocation failed", STDERR_FILENO);
	else if (error == 3)
	{
		g_exit = 1;
		error_errno();
	}
	else if (error == 4)
	{
		g_exit = 258;
		ft_putendl_fd("minishell: Syntax error", STDERR_FILENO);
	}
}
