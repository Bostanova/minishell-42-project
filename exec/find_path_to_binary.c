#include "../includes/minishell.h"

char	**get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], "PATH=", 5)))
			path = ft_split(env[i], ':');
		i++;
	}
	path[0] = ft_copy(path[0], 5);
	i = 0;
	while (path[i])
	{
		path[i] = ft_join(path[i], "/");
		i++;
	}
	return (path);
}

char	*test_path(char **path, char *cmd){
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (path[i])
	{
		path[i] = ft_join(path[i], cmd);
		if (!(access(path[i], X_OK)))
		{
			res = (char *)malloc(ft_strlen(path[i] + 1));
			j = 0;
			while (path[i][j])
			{
				res[j] = path[i][j];
				j++;
			}
			res[j] = '\0';
			return (res);
		}	
		i++;
	}
	error_cmd_not_found(127, cmd);
	return (NULL);
}