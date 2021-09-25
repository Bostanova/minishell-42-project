#include "../includes/minishell.h"

void	env_cmd(t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		write(STDOUT_FILENO, cmd->env[i], ft_strlen(cmd->env[i]) + 1);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
