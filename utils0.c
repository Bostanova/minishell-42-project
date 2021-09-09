#include "./includes/minishell.h"

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char	*rl_gets (void) {
	char *line;
	
	line = (char *)NULL;
  	if (line)
	{
		free (line);
		line = (char *)NULL;
	}
	line = readline (PROMPT);
	if (line && *line) 
		add_history (line);
	return (line);
}

t_cmds	*init_cmd(char **env) {
	t_cmds	*cmd;

	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmd)
		ft_error(1);
	cmd->env = env;
	cmd->args = NULL;
	cmd->count_args = 0;
	cmd->redir[0] = 0;
	cmd->redir[1] = 0;
	cmd->pipe = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	return (cmd);
}

char	**get_env(char **envp) {
	char	**res;
	int		i;

	i = 0;
	while (envp[i]) {
		i++;
	}
	if (!(res = (char **)malloc(sizeof(char *) * (i + 2)))) {
		exit(1);
	}
	i = 0;
	while (envp[i]) {
		res[i] = ft_strdup(envp[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

