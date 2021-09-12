#include "../includes/minishell.h"

void	printing(t_env *env) {
	while (env) {
		if ((ft_strcmp(env->name, "_"))) {
			printf("declare -x %s=%s\n", env->name, env->data);
		}
		env = env->next;
	}
}

void	change_env()
{
	
}

void	export_cmd(t_cmds *cmd, t_env *env) {
	int	i;

	i = 1;
	if (!cmd->args[1]) {
		printing(env);
	}
	else {
		while(cmd->args[i]) {
			change_env(env, cmd->args[i]);		
			i++;
		}
	}
}
