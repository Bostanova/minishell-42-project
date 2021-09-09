#include "./includes/minishell.h"

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
	if (line[*i] == '\'' || line[*i] == '\"') {
		env = quote_proccesing(line, i);
	}
	else {
		while (line[*i] && !stophere(line[*i])) {
			env = add_char(env, line[*i]);
			*i += 1;
		}
	}
	return (env);
}

static char	*add_str(char *s1, char *s2, int start) {
	char	*res;
	int		j;

	j = start;
	while (s2[j]) {
		j += 1;
	} 
	res = (char *)malloc(ft_strlen(s1) + (j - start + 1) + 1);
	if (!res)
		ft_error(1);
	j = 0;
	if (s1)
		while(s1[j]) {
			res[j] = s1[j];
			j++;
		}
	while(s2[start]) {
		res[j] = s2[start];
		j += 1;
		start += 1;
	}
	res[j] = '\0';
	if (s1) 
		free(s1);
	return (res);
}

void	parse_env(t_cmds *cmd, char *line, int *i) {
	char *env;
	int j;
	int len;

	env = get_envs_name(line, i);
	j = 0;
	len = ft_strlen(env);
	while (cmd->env[j]) {
		if (!ft_strncmp(cmd->env[j], env, len)) {
			len += 1;
			cmd->args[cmd->count_args] = add_str(cmd->args[cmd->count_args], cmd->env[j], len);
		}
		j += 1;
	}
	if (env)
		free(env);
}
