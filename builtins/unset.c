#include "../includes/minishell.h"

void	create_new_env(char ***env, int len, int skip){
	char	**res;
	int		g;
	int		j;

	res = (char **)malloc(sizeof(char *) * len);
	res[len - 1] = NULL;
	g = 0;
	j = 0;
	while ((*env)[g]) {
		if (g == skip)
			g++;
		res[j] = ft_strdup((*env)[g]);
		g++;
		j++;
	}
	free_env(env);
	*env = res;
}

void	del_env(char ***env, char *str){
	int		h;
	int		index;
	char	*tmp;

	h = 0;
	index = 0;
	tmp = ft_strdup(str);
	tmp = ft_join(tmp, "=");
	while ((*env)[h]) {
		if (!(ft_strncmp((*env)[h], tmp, ft_strlen(tmp)))) 
			index = h;
		h++;
	}
	free(tmp);
	if (index)
		create_new_env(env, h, index); 
}

void	del_env_with_value(char ***env, char *str){
	int	i;
	int	index;

	i = 0;
	index = 0;
	if (str[ft_strlen(str) - 1] == '=')
		error_unset(1, str);
	while ((*env)[i]) {
		if (!(ft_strcmp((*env)[i], str))) 
			index = i;
		i++;
	}
	if (index)
		create_new_env(env, i, index);
	else
		error_unset(1, str);
}

void	unset_cmd(t_cmds *cmd, char ***env) {
	int	i;

	i = 1;
	while(cmd->args[i]) {
		if (cmd->args[i][0] == '=' || ft_isdigit(cmd->args[i][0]))
			error_unset(1, cmd->args[i]);
		else if (ft_strchr(cmd->args[i], '='))
			del_env_with_value(env, cmd->args[i]);
		else
			del_env(env, cmd->args[i]);
		i++;
	}
}