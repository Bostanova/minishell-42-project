#include "./includes/minishell.h"

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
			parse_env(cmd, line, i);
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
