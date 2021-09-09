#include "./includes/minishell.h"

void	parse_single_quotes(t_cmds *cmd, char *line, int *i) {
	*i += 1;
	while (line[*i] != '\'') {
		cmd->args[cmd->count_args] = add_char(cmd->args[cmd->count_args], line[*i]);
		*i += 1;
	}
	*i += 1;
}

void	parse_double_quotes(t_cmds *cmd, char *line, int *i) {
	*i += 1;
	
	while (line[*i] != '\"') {
		if (line[*i] == '$') {
			parse_env(cmd, line, i);
		}
		else {
			cmd->args[cmd->count_args] = add_char(cmd->args[cmd->count_args], line[*i]);
			*i += 1;
		}
	}
	*i += 1;
}
