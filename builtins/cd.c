/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:31:54 by eerika            #+#    #+#             */
/*   Updated: 2021/10/04 18:44:14 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(char ***env)
{
	int	i;

	i = 0;
	if (*env)
	{
		while ((*env)[i])
		{
			free((*env)[i]);
			i++;
		}
		free(*env);
	}
}

static void	fill_oldpwd(char ***env, char *oldpwd, int size)
{
	char	**res;
	int		i;

	res = (char **)malloc(sizeof(char *) * (size + 2));
	if (!res)
		ft_error(1);
	i = 0;
	while ((*env)[i])
	{
		res[i] = ft_strdup((*env)[i]);
		i++;
	}
	res[i] = ft_strdup("OLDPWD=");
	res[i] = ft_join(res[i], oldpwd);
	res[i + 1] = NULL;
	free_env(env);
	*env = res;
}

static void	rewrite_env(char ***env, char *pwd, int i, int which_env)
{
	char	*tmp;

	if (which_env == 1)
		tmp = ft_strdup("PWD=");
	else
		tmp = ft_strdup("OLDPWD=");
	tmp = ft_join(tmp, pwd);
	free((*env)[i]);
	(*env)[i] = tmp;
}

static void	change_env_pwd(char ***env, char *pwd, char *oldpwd)
{
	int		i;
	int		sign;
	char	*tmp;

	sign = 0;
	i = 0;
	while ((*env)[i])
	{
		if (!(strncmp((*env)[i], "PWD=", 4)))
			rewrite_env(env, pwd, i, 1);
		else if (!(strncmp((*env)[i], "OLDPWD=", 7)))
		{
			rewrite_env(env, oldpwd, i, 0);
			sign = 1;
		}
		i++;
	}
	if (sign == 0)
		fill_oldpwd(env, oldpwd, i + 1);
}

void	cd_cmd(t_cmds *cmd, char ***env)
{
	char		*pwd;
	char		*oldpwd;
	struct stat	stats;

	oldpwd = getcwd(NULL, 0);
	if (stat(cmd->args[1], &stats) == 0)
	{
		chdir(cmd->args[1]);
		pwd = getcwd(NULL, 0);
		change_env_pwd(env, pwd, oldpwd);
		if (pwd)
			free(pwd);
	}
	else
	{
		if (errno)
			printf ("minishell: cd: %s\n", strerror(errno));
	}
	if (oldpwd)
		free(oldpwd);
}
