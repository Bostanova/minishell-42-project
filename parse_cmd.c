#include "./includes/minishell.h"

int	is_new_arg(char c) {
	if (c == '<' || c == '>' || c == '|' || ft_isspace(c))
		return (1);
	else
		return (0);
}

char	**global_alloc(char **arr, int size) {
	char	**res;
	int		i;

	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (!res)
		ft_error(1);
	i = 0;
	if (arr) {
		while (i < size - 1) {
			res[i] = ft_strdup(arr[i]);
			i++;
		}
	}
	res[i] = NULL;
	res[i + 1] = NULL;
	if (arr)
		free_arr(arr);
	return (res);
}

char	*add_char(char *str, char c) {
	char	*res;
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

static int	isinterpret(char c) {
	if (c == '\'' || c == '\"' || c == '<' \
		|| c == '>' || c == '$' || c == '|' \
		|| ft_isspace(c))
		return (1);
	else
		return (0);
}

void	parse_cmd(t_cmds *cmd, char *line, int *i) {
	while(!isinterpret(line[*i]) && line[*i]) {
		cmd->args[cmd->count_args] = add_char(cmd->args[cmd->count_args], line[*i]);
		*i += 1;
	}
}
