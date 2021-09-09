// done

#include "../includes/minishell.h"

void	env_cmd(char **g_envp)
{
	int	i;

	i = 0;
	while (g_envp[i])
	{
		printf("%s\n", g_envp[i]);
		i++;
	}
}
