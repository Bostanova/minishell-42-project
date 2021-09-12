#include "../includes/minishell.h"

void	env_cmd(t_cmds *cmd)
{
	while (cmd->env)
	{
		printf("%s=%s\n", cmd->env->name, cmd->env->data);
		cmd->env = cmd->env->next;
	}
}
