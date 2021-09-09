#include "../includes/minishell.h"

void	free_arr(char **arr) {
	int i;
	
	i = 0;
	if (arr) {
		while (arr[i]) {
			free(arr[i]);
			i++;
		}
	}
	free(arr);
}

void	free_cmd(t_cmds *cmd) {
	int 	i;
	t_cmds *tmp;

	while (cmd) {
		tmp = cmd;
		i = 0;
		if (cmd->args) {
			while (i < cmd->count_args) {
			free(cmd->args[i]);
			i++;
			}
		free(cmd->args);
		}
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
		cmd = tmp->next;
	}

	
}

void	ft_error(int err) {
	if (err == 1)
		printf("Error: cannot allocate memory\n");
	exit(err);
}
