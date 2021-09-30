//вызывать и для Echo

#include "../includes/minishell.h"

void	print_echo(char **args) {
	int i;

	i = 1;
	if (!(ft_strcmp(args[1], "-n")))
		i++;
	while (args[i] && args[i + 1]) {
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
}

void	echo_cmd(t_cmds *cmd)
{
	if (cmd->args[1]) {
		print_echo(cmd->args);
	}
	else
		write(STDOUT_FILENO, "\n", 1);
	if (cmd->args[1]) {
		if (ft_strcmp(cmd->args[1], "-n"))
		write(STDOUT_FILENO, "\n", 1);
	}
}
