#include "../includes/minishell.h"

void	print_echo(char **args) {
	int i;

	i = 2;
	while (args[i] && args[i + 1]) {
		printf("%s ", args[i]);
		i += 1;
	}
	printf("%s", args[i]);
}

void	echo_cmd(t_cmds *cmd)
{
	if (cmd->args[1]) {
		print_echo(cmd->args);
		if ((ft_strncmp(cmd->args[1], "-n", 2))) {
			printf("\n");
		}
	}
	else {
		printf("\n");
	}
}
