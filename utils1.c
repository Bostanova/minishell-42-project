#include "./includes/minishell.h"

void	free_arr(char **arr) {
	int i = 0;

	if (arr)
		while (arr[i]) {
			free(arr[i]);
			i++;	
		}
	if (arr)
		free(arr);
}

void	free_cmd(t_cmds *cmd) {
	free_arr(cmd->args);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	free(cmd);
}

void	ft_error(int err)
{
	if (err == 1)
		printf("Error: cannot allocate memory\n");
	exit(err);
}


