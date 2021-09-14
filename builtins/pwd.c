#include "../includes/minishell.h"

void	pwd_cmd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir) {
		printf("%s\n", current_dir);
	free(current_dir);
	}
	else {
		if (errno)
			printf("minishell: pwd: %s\n", strerror(errno));
	}
}
