// done

#include "../includes/minishell.h"

void	pwd_cmd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	printf("%s\n", current_dir);
	free(current_dir);
}
