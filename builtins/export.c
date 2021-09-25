#include "../includes/minishell.h"
//I have to do that :((
void	printing(char ***env) {
	printf("1\n");
}

void	add_env(char ***env, char *str, int size) {
	char **res;
	int	i;

	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (!res)
		ft_error(1);
	i = 0;
	while ((*env)[i]) {
		res[i] = ft_strdup((*env)[i]);
		i++;
	}
	res[i] = ft_strdup(str);
	res[i + 1] = NULL;
	free_env(env);
	*env = res;
}

void	change_env(char ***env, char *str) {
	int		size_cmp;
	int		i;
	int		sign;
	char	*tmp;
	
	size_cmp = 0;
	while (str[size_cmp] != '=')
		size_cmp++;
	size_cmp++;
	i = 0;
	sign = 0;
	while((*env)[i]) {
		if (!(ft_strncmp((*env)[i], str, size_cmp))){
			tmp = ft_strdup(str);
			free((*env)[i]);
			(*env)[i] = tmp;
			sign = 1;
		}
		i++;
	}
	if (sign == 0)
		add_env(env, str, i + 1);
}

void	export_cmd(t_cmds *cmd, char ***env) {
	int	i;

	i = 1;
	if (!cmd->args[1]) {
		printing(env);
	}
	else {
		while(cmd->args[i] && ft_strchr(cmd->args[i], '=')) {
			if (cmd->args[i][0] == '=' || ft_isdigit(cmd->args[i][0]))
				error_export(1, cmd->args[i]);
			else
				change_env(env, cmd->args[i]);
			i++;
		}
	}
}
