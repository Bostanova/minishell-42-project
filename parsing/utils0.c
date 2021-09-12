#include "../includes/minishell.h"

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

t_cmds	*init_cmd(t_env *env) {
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

t_env *addelem(t_env *lst, char *name, char *data)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	while(lst && lst->next)
		 lst = lst->next;
	lst->next = new_node;
	new_node->name = ft_strdup(name);
	new_node->data = ft_strdup(data);
	new_node->next = NULL;
	return(new_node);
}

t_env	*get_array_of_env(char **envp) {
	t_env *res;
	t_env *head;
	char **tmp;
	int		i;

	i = 0;
	res = (t_env *)malloc(sizeof(t_env));
	tmp = ft_split(envp[i], '=');
	res->name = ft_strdup(tmp[0]);
	res->data = ft_strdup(tmp[1]);
	res->next = NULL;
	head = res;
	free_arr(tmp);
	i = 1;
	while (envp[i]) {
		tmp = ft_split(envp[i], '=');
		addelem(res, tmp[0], tmp[1]);
		i++;
		free_arr(tmp);
	}
	res = head;
	return (res);
}
