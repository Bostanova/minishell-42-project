#include "./includes/minishell.h"

static int	isinterpret(char c) {
	if (c == '\'' || c == '\"' || c == '<' \
		|| c == '>' || c == '$' || c == '|' \
		|| ft_isspace(c))
		return (1);
	else
		return (0);
}

static char	**ft_global_realloc(char **arr, int size) {
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
	res[i+1] = NULL;
	if (arr)
		free_arr(arr);
	return (res);
}
//добавление символа к строке через маллок, строка остается нуль-терминированной
//вызывается также при парсинге одинарных кавычек parse_single_quotes
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

void	parse_cmd(t_cmds *cmd, char *line, int *i) {
	int index;

	index = cmd->count_args;
	
	cmd->args = ft_global_realloc(cmd->args, (1 + cmd->count_args));
	while(!isinterpret(line[*i]) && line[*i]) {
		cmd->args[index] = add_char(cmd->args[index], line[*i]);
		*i += 1;
	}
	cmd->count_args += 1;
}
