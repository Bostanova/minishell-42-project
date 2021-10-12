/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feschall <feschall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:27:48 by feschall          #+#    #+#             */
/*   Updated: 2021/10/11 16:47:19 by feschall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_cmd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir)
	{
		printf("%s\n", current_dir);
		free(current_dir);
		g_exit = 0;
	}
	else
	{
		if (errno)
			printf("minishell: pwd: %s\n", strerror(errno));
	}
}
