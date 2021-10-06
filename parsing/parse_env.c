#include "../includes/minishell.h"

static int	stophere(char c)
{
	if (c == '<' || c == '\'' || c == '\"' \
		|| c == '>' || c == '|' || ft_isspace(c))
		return (1);
	return (0);
}

static char	*get_envs_name(char *line, int *i)
{
	char	*env;

	env = NULL;
	*i += 1;
	while (line[*i] && !stophere(line[*i]))
	{
		env = add_char(env, line[*i]);
		*i += 1;
	}
	env = add_char(env, '=');
	return (env);
}

static char	*add_str(char *s1, char *s2, int start)
{
	char	*res;
	int		j;
	int		k;

	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) - start + 1);
	if (!res)
		ft_error(1);
	j = 0;
	if (s1)
	{
		while (s1[j])
		{
			res[j] = s1[j];
			j++;
		}
	}
	k = start;
	while (s2[k])
		res[j++] = s2[k++];
	res[j] = '\0';
	if (s1)
		free(s1);
	return (res);
}

void	parse_env_help(char *env, t_cmds *cmd, int redir)
{
	int	j;

	j = 0;
	while (cmd->env[j])
	{
		if (!(ft_strncmp(cmd->env[j], env, ft_strlen(env))))
		{
			if (redir == LESS)
				cmd->infile = add_str(cmd->infile, cmd->env[j], ft_strlen(env));
			else if (redir == GREAT || redir == GREATGREAT)
			{
				cmd->outfile = \
				add_str(cmd->outfile, cmd->env[j], ft_strlen(env));
			}	
			else
				cmd->args[cmd->count_args] = \
				add_str(cmd->args[cmd->count_args], \
				cmd->env[j], ft_strlen(env));
		}
		j++;
	}
}

void	parse_env(t_cmds *cmd, char *line, int *i, int redir)
{
	char	*env;
	char	*tmp;

	if (ft_isspace(line[*i + 1]))
	{
		cmd->args[cmd->count_args] = \
		add_char(cmd->args[cmd->count_args], line[*i]);
		*i += 1;
	}
	else if (line[*i + 1] == '?')
	{
		tmp = ft_itoa(g_exit);
		cmd->args[cmd->count_args] = \
		add_str(cmd->args[cmd->count_args], tmp, 0);
		*i += 2;
		free(tmp);
	}
	else
	{
		env = get_envs_name(line, i);
		parse_env_help(env, cmd, redir);
		if (env)
			free(env);
	}
}
