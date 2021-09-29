#include "../includes/minishell.h"

int	check_buildin(char *cmd)
{
	if (!strcmp(cmd, "cd") || !strcmp(cmd, "echo")\
		|| !strcmp(cmd, "Echo") || !strcmp(cmd, "exit")\
		|| !strcmp(cmd, "export") || !strcmp(cmd, "pwd")\
		|| !strcmp(cmd, "unset") || !strcmp(cmd, "env") )
		return (1);
	return (0);
}

void	exec_buildins(t_cmds *cmd, char ***env)
{
	if (!strcmp(cmd->args[0], "cd"))
		cd_cmd(cmd, env);
	else if (!strcmp(cmd->args[0], "echo") || !strcmp(cmd->args[0], "Echo"))
		echo_cmd(cmd);
	else if (!strcmp(cmd->args[0], "exit"))
		exit_cmd(cmd);
	else if (!strcmp(cmd->args[0], "env"))
		env_cmd(cmd);
	else if (!strcmp(cmd->args[0], "pwd"))
		pwd_cmd();
	else if (!strcmp(cmd->args[0], "unset"))
		unset_cmd(cmd, env);
	else
		export_cmd(cmd, env);
}
