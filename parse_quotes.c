#include "./includes/minishell.h"

void	parse_single_quotes(t_cmds *cmd, char *line, int *i) {
	*i += 1; 		//перевод на след символ после открывающей кавычки
	cmd->args = global_alloc(cmd->args, (1 + cmd->count_args));
	while (line[*i] != '\'') {
		cmd->args[cmd->count_args] = add_char(cmd->args[cmd->count_args], line[*i]);
		*i += 1;
	}
	cmd->count_args += 1;
	*i += 1; 		//пропускаю закрывающую кавычку
}
