#include "../includes/minishell.h"

void	pwd_cmd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir)
	{
		write(STDOUT_FILENO, current_dir, ft_strlen(current_dir) + 1);
		write(STDOUT_FILENO, "\n", 1);
		free(current_dir);
		g_exit = 0;	
	}
	else
	{
		if (errno)
		{
			printf("minishell: pwd: %s\n", strerror(errno));
		}
	}
}
