#include "../includes/minishell.h"

static int stoping(char c) {
	if (c == '<' || c == '>' || c == '|' || ft_isspace(c)) {
			return 1;
		}
	return 0;
}

void	parse_input(t_cmds *cmd, char *line, int *i) {
	while (ft_isspace(line[*i])) {
		*i += 1;
	}
	while (line[*i] && !stoping(line[*i])) {
		if (line[*i] == '\'') {
			parse_single_quotes(cmd, line, i, cmd->redir[0]);
		}
		else if (line[*i] == '\"') {
			parse_double_quotes(cmd, line, i, cmd->redir[0]);
		}
		else if (line[*i] == '$') {
			parse_env(cmd, line, i, cmd->redir[0]);
		}
		else {
			cmd->infile = add_char(cmd->infile, line[*i]);
			*i += 1;
		}
	}
}

void	parse_output(t_cmds *cmd, char *line, int *i) {
	while (ft_isspace(line[*i])) {
		*i += 1;
	}
	while (line[*i] && !stoping(line[*i])) {
		if (line[*i] == '\'') {
			parse_single_quotes(cmd, line, i, cmd->redir[1]);
		}
		else if (line[*i] == '\"') {
			parse_double_quotes(cmd, line, i, cmd->redir[1]);
		}
		else if (line[*i] == '$') {
			parse_env(cmd, line, i, cmd->redir[1]);
		}
		else {
			cmd->outfile = add_char(cmd->outfile, line[*i]);
			*i += 1;
		}
	}
}

int	parse_redirect(t_cmds *cmd, char *line, int *i) {
	if (line[*i] == '<') {
		if (line[*i + 1] == '<') {
			cmd->redir[0] = LESSLESS;
			*i += 1;
		}
		else if (line[*i + 1] == '>') {
			cmd->redir[1] = GREAT;
			*i += 2;
			parse_output(cmd, line, i);
		}
		else {
			cmd->redir[0] = LESS;
		}
		*i += 1;
		parse_input(cmd, line, i);
	}
	else {
		if (line[*i + 1] == '<') {
			g_exit = 258;
			printf("minishell: syntax error near unexpected token '<'\n");
			return (1);
		}
		else if (line[*i + 1] == '>') {
			cmd->redir[1] = GREATGREAT;
			*i += 2;
			parse_output(cmd, line, i);
		}
		else {
			cmd->redir[1] = GREAT;
			*i += 1;
			parse_output(cmd, line, i);
		}
	}
	return (0);
}