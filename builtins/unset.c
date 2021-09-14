#include "../includes/minishell.h"

void	unset_cmd(t_cmds *cmd, t_env *env) {
	int 	k;
	t_env	*tmp;

	k = 1;
	while (k < cmd->count_args) {
		tmp = env;
		while (tmp) {
			if (!(ft_strcmp(tmp->name, cmd->args[k])))
				env = delelem(env, cmd->args[k]);
			tmp = tmp->next;
		}
		k++;
	}
}