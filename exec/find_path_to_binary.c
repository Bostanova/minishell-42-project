/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_to_binary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:33:59 by eerika            #+#    #+#             */
/*   Updated: 2021/10/11 16:38:01 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **env)
{
	int		i;
	char	**path;

	i = -1;
	path = NULL;
	while (env[++i])
		if (!(ft_strncmp(env[i], "PATH=", 5)))
			path = ft_split(env[i], ':');
	if (path)
	{
		path[0] = ft_copy(path[0], 5);
		i = -1;
		while (path[++i])
			path[i] = ft_join(path[i], "/");
	}
	return (path);
}

char	*test_path(char **path, char *cmd)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	while (path[++i])
	{
		path[i] = ft_join(path[i], cmd);
		if (!(access(path[i], X_OK)))
		{
			res = (char *)malloc(ft_strlen(path[i] + 1));
			if (!res)
				ft_error(1);
			j = -1;
			while (path[i][++j])
				res[j] = path[i][j];
			res[j] = '\0';
			return (res);
		}
	}
	error_cmd_not_found(cmd);
	return (NULL);
}
