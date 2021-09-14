#include "../includes/minishell.h"

static char *quote_proccesing(char *line, int *i) {
	char *env;

	env = NULL;
	if (line[*i] == '\'') {
		*i += 1;
		while (line[*i] != '\'') {
			env = add_char(env, line[*i]);
			*i += 1;
		}
		*i += 1;
	}
	else if (line[*i] == '"') {
		*i += 1;
		while (line[*i] != '"') {
			env = add_char(env, line[*i]);
			*i += 1;
		}
		*i += 1;
	}
	return (env);
}

static int stophere(char c) {
	if (c == '<' || c == '\'' || c == '\"' \
		|| c == '>' || c == '|' || ft_isspace(c)) {
			return 1;
		}
	return 0;
}

static char *get_envs_name(char *line, int *i) {
	char *env;

	env = NULL;
	*i += 1;
	while (line[*i] && !stophere(line[*i])) {
		env = add_char(env, line[*i]);
		*i += 1;
	}
	return (env);
}

static char	*add_str(char *s1, char *s2) {
	char	*res;
	int		j;
	int		k;

	j = 0;
	while (s2[j]) {
		j += 1;
	} 
	res = (char *)malloc(ft_strlen(s1) + (j + 1) + 1);
	if (!res)
		ft_error(1);
	j = 0;
	if (s1)
		while(s1[j]) {
			res[j] = s1[j];
			j++;
		}
	k = 0;
	while(s2[k]) {
		res[j++] = s2[k++];
	}
	res[j] = '\0';
	if (s1) 
		free(s1);
	return (res);
}

void	parse_env(t_cmds *cmd, char *line, int *i, int redir) {
	char *env;
	int j;

	if (ft_isspace(line[*i + 1])) {
		cmd->args[cmd->count_args] = add_char(cmd->args[cmd->count_args], line[*i]);
		*i += 1;
	}
	else {
		env = get_envs_name(line, i);
		j = 0;
		while (cmd->env) {
			if (!(ft_strcmp(cmd->env->name, env))) {
				if (redir == LESS || redir == LESSLESS) {
					cmd->infile = add_str(cmd->infile, cmd->env->data);
				}
				else if (redir == GREAT || redir == GREATGREAT) {
					cmd->outfile = add_str(cmd->outfile, cmd->env->data);
				}
				else {
					cmd->args[cmd->count_args] = add_str(cmd->args[cmd->count_args], cmd->env->data);
				}
			}
			cmd->env = cmd->env->next;
		}
		if (env)
			free(env);
	}
}
