#include "./includes/minishell.h"

int	foo(char c) {
	if ((c >= '!' && c <= ';') || c == '=') {
		return (1);
	}
	else if (c >= '?' && c <= '{') {
			return (1);
	}
	else if (c >= '}' && c <= '~') {
			return (1);
	}
	return (0);
}

static void	alloc_new_arg(t_cmds *cmd, char *line, int *i) {
	if (*i == 0 || cmd->count_args == 0) {
		cmd->args = global_alloc(cmd->args, 1);
	}
	else if (ft_isspace(line[*i - 1]) && foo(line[*i])) {
		cmd->args = global_alloc(cmd->args, (1 + cmd->count_args));
	}
	else if (line[*i] == '<') {
		if (cmd->infile) {
			free(cmd->infile);
			cmd->infile = NULL;
		}
	}
	else if (line[*i] == '>') {
		if (cmd->outfile) {
			free(cmd->outfile);
			cmd->outfile = NULL;
		}
	}
}

void	parsing(t_cmds *cmd, char *line, char **env) {
	int *i;
	
	i = (int *)malloc(sizeof(int));
	*i = 0;
	while (line[*i]) {
		alloc_new_arg(cmd, line, i);
		if (ft_isspace(line[*i])) {
			*i += 1;
		}
		else if (line[*i] == '\'') {
			parse_single_quotes(cmd, line, i, 0);
		}
		else if (line[*i] == '\"') {
			parse_double_quotes(cmd, line, i, 0);
		}
		else if (line[*i] == '<' || line[*i] == '>') {
			parse_redirect(cmd, line, i);
			}
		else if (line[*i] == '$') {
			parse_env(cmd, line, i, 0);
		}
		else if (line[*i] == '|') {
			cmd->pipe = 1;
			cmd->next = init_cmd(env);
			cmd = cmd->next;
			*i += 1;
		}
		else {
			parse_cmd(cmd, line, i);
		}
		if ((!line[*i] || is_new_arg(line[*i])) && cmd->args) {
			if (cmd->args[cmd->count_args])
				cmd->count_args += 1;
		}
	}
	free(i);
}
