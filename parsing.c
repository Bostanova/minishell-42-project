#include "./includes/minishell.h"

char **ft_global_realloc(char **arr) {
	char	**res;
	int		i;

	i = 1;
	if (arr) {
		while (arr[i]) {
			i++;	
		}
	}
	res = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	if (arr)
		while (arr[i]) {
			res[i] = ft_strdup(arr[i]);
			i++;
		}
	res[i] = NULL;
	if (arr)
		free_arr(arr);
	return (res);
}

char *re_alloc(char *str, char c) {
	char *res;
	int		j;

	res = (char *)malloc(ft_strlen(str) + 2);
	if (!res)
		ft_error(1);
	j = 0;
	if (str)
		while(str[j]) {
			res[j] = str[j];
			j++;
		}
	res[j] = c;
	res[j + 1] = '\0';
	if (str) 
		free(str);
	return (res);
}

void parse_cmd(t_cmds *cmd, char *line, int *i) {
	int index;

	index = cmd->count_args;
	cmd->count_args += 1;
	cmd->args = ft_global_realloc(cmd->args);
	while(line[*i] != '\0') {
		cmd->args[index] = re_alloc(cmd->args[index], line[*i]);
		*i += 1;
	}
}

void	parsing(t_cmds *cmd, char *line) {
	int *i;
	
	i = (int *)malloc(sizeof(int));
	*i = 0;
	while (line[*i]) {
		if (line[*i] == ' ')
			*i += 1;
		else {
			parse_cmd(cmd, line, i);
		}
	}
	free(i);
}
