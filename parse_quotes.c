#include "./includes/minishell.h"

void	parse_single_quotes(t_cmds *cmd, char *line, int *i, int redir) {
	*i += 1;
	while (line[*i] != '\'') {
		if (redir == LESS || redir == LESSLESS) {
			cmd->infile = add_char(cmd->infile, line[*i]);
		}
		else if (redir == GREAT || redir == GREATGREAT) {
			cmd->outfile = add_char(cmd->outfile, line[*i]);
		}
		else {
			cmd->args[cmd->count_args] = add_char(cmd->args[cmd->count_args], line[*i]);
		}
		*i += 1;
	}
	*i += 1;
}

void	parse_double_quotes(t_cmds *cmd, char *line, int *i, int redir) {
	*i += 1;
	
	while (line[*i] != '\"') {
		if (line[*i] == '$') {
			parse_env(cmd, line, i, redir);
		}
		else {
			if (redir == LESS || redir == LESSLESS) {
				cmd->infile = add_char(cmd->infile, line[*i]);
			}
			else if (redir == GREAT || redir == GREATGREAT) {
				cmd->outfile = add_char(cmd->outfile, line[*i]);
			}
			else {
				cmd->args[cmd->count_args] = add_char(cmd->args[cmd->count_args], line[*i]);
			}
			*i += 1;
		}
	}
	*i += 1;
}
