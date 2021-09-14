#include "../includes/minishell.h"

void	printing(t_env *env) {
	while (env) {
		if ((ft_strcmp(env->name, "_"))) {
			printf("declare -x %s=%s\n", env->name, env->data);
		}
		env = env->next;
	}
}

void	change_env(t_env *env, char *args)
{
	t_env	*tmp;
	char	**env_data;
	
	env_data = ft_split(args, '=');
	if (!env_data[0]){
		error_export(1, "not a valid identifiers");
	}
	if (!env_data[1]) {
		env_data[1] = (char *)malloc(2);
		ft_strcpy(env_data[1], " ");
	}
	tmp = env;
	while (tmp) {
		if (!(ft_strcmp(tmp->name, env_data[0])))
			env = delelem(env, env_data[0]);
		tmp = tmp->next;
	}
	env = addelem(env, env_data[0], env_data[1]);
	if (env_data) {
		free_arr(env_data);
	}
}

void	export_cmd(t_cmds *cmd, t_env *env) {
	int	k;

	k = 1;
	if (!cmd->args[1]) {
		printing(env);
	}
	else {
		while(cmd->args[k] && ft_strchr(cmd->args[k], '=')) {
			change_env(env, cmd->args[k]);	
			k++;
		}
	}
}
