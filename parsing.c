#include "./includes/minishell.h"

static void	alloc_new_arg(t_cmds *cmd, char *line, int *i) {
	if (*i == 0) {
		cmd->args = global_alloc(cmd->args, 1);
	}
	else if (line[*i] == '<' || line[*i] == '>' \
		|| (ft_isspace(line[*i - 1]) && ( ft_isalnum(line[*i]) \
		|| line[*i] == '$' || line[*i] == '\'' || line[*i] == '\"'))) {
		cmd->args = global_alloc(cmd->args, (1 + cmd->count_args));
	}
}

void	parsing(t_cmds *cmd, char *line) {
	int *i;
	
	i = (int *)malloc(sizeof(int));
	*i = 0;
	while (line[*i]) {
		alloc_new_arg(cmd, line, i);
		if (ft_isspace(line[*i])) {
			*i += 1;
		}
		else if (line[*i] == '\'') {
			parse_single_quotes(cmd, line, i);
		}
		else if (line[*i] == '\"') {
			parse_double_quotes(cmd, line, i);
		}
		else if (line[*i] == '<' || line[*i] == '>') {
			*i + = 1;
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
		if (!line[*i] || is_new_arg(line[*i])) {
			if (cmd->args[cmd->count_args])
				cmd->count_args += 1;
		}
	}
	free(i);
}
