/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:47:11 by eerika            #+#    #+#             */
/*   Updated: 2021/10/09 16:47:53 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**sort_env(char **env, int len)
{
	int		i;
	int		j;
	char	**new;
	char	*tmp;

	new = (char **)malloc(sizeof(char *) * (len + 1));
	new[len] = NULL;
	i = -1;
	while (env[++i])
		new[i] = ft_strdup(env[i]);
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len - 1)
		{
			if (ft_strncmp(new[j], new[j + 1], ft_strlen(new[j]) + 1) > 0)
			{
				tmp = new[j + 1];
				new[j + 1] = new[j];
				new[j] = tmp;
			}
		}
	}
	return (new);
}

static void	printing(char **env)
{
	char	**sort;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	sort = sort_env(env, i);
	i = -1;
	while (sort[++i])
	{
		// ft_putnbr_fd(i, 1);
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (sort[i][j] && sort[i][j] != '=')
			ft_putchar_fd(sort[i][j++], 1);
		if (sort[i][j])
		{
			ft_putchar_fd(sort[i][j++], 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(sort[i] + j, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
	}
	free_arr(sort);
}

void	add_env(char ***env, char *str, int size)
{
	char	**res;
	int		i;

	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (!res)
		ft_error(1);
	i = -1;
	while ((*env)[++i])
		res[i] = ft_strdup((*env)[i]);
	res[i] = ft_strdup(str);
	res[i + 1] = NULL;
	free_env(env);
	*env = res;
}

void	change_env(char ***env, char *str)
{
	int		size_cmp;
	int		i;
	int		sign;
	char	*tmp;

	size_cmp = 0;
	while (str[size_cmp] && str[size_cmp] != '=')
		size_cmp++;
	i = 0;
	sign = 0;
	while ((*env)[i])
	{
		if (!(ft_strncmp((*env)[i], str, size_cmp + 1)))
		{
			tmp = ft_strdup(str);
			free((*env)[i]);
			(*env)[i] = tmp;
			sign = 1;
		}
		i++;
	}
	if (sign == 0)
		add_env(env, str, i + 1);
}

void	export_cmd(t_cmds *cmd, char ***env)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
	{
		printing(*env);
		g_exit = 0;
	}
	else
	{
		while (cmd->args[i])
		{
			if (cmd->args[i][0] == '=' || ft_isdigit(cmd->args[i][0]))
			{
				g_exit = 1;
				error_export(cmd->args[i]);
			}
			else
			{
				change_env(env, cmd->args[i]);
				g_exit = 0;
			}
			i++;
		}
	}
}
