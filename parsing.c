#include "./includes/minishell.h"

void	parse_single_quotes(t_cmds *cmd, char *line, int *i) {
	char	*tmp;
	char	**res;
	int		j;

	tmp	= NULL;
	*i += 1; //перевод на след символ после открывающей кавычки
	while(line[*i] != '\'') {
		tmp = add_char(tmp, line[*i]);
		*i += 1;
	}
	*i += 1; //пропускаю закрывающую кавычку
	res = ft_split_with_spaces(tmp);
	j = 0;
	while (res[j]) {
		cmd->args[cmd->count_args] = ft_strdup(res[j]);
		j += 1;
		cmd->count_args += 1;
	}
	free(tmp);
	free_arr(res);
}

void	parsing(t_cmds *cmd, char *line) {
	int *i;
	
	i = (int *)malloc(sizeof(int));
	*i = 0;
	while (line[*i]) {
		if (ft_isspace(line[*i])) {
			*i += 1;
		}
		else if (line[*i] == '\'') {
			parse_single_quotes(cmd, line, i);
		}
		else if (line[*i] == '\"') {
			*i += 1;
		}
		else if (line[*i] == '<' || line[*i] == '>') {
			// printf("3\n");
			*i += 1;
		}
		else if (line[*i] == '$') {
			// printf("4\n");
			*i += 1;
		}
		else if (line[*i] == '|') {
			// printf("5\n");
			*i += 1;
		}
		else {
			parse_cmd(cmd, line, i);
		}
	}
	free(i);
}
