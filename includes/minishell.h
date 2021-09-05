#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>				//strerror, etc
 #include <sys/stat.h> 			//for stat
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

#define PROMPT "bigSmile> "
#define TRUE 1
#define GREAT 1
#define LESS 2
#define GREATGREAT 3
#define LESSLESS 4

int		g_exit;

typedef struct s_cmds
{
	char			**env;
	char			**args;		//args[0] - name of command
	int				count_args;
	int				pipe;
	int				redir[2];	//redir[0] - наличие редиректа, redir[1] - символ редиректа: > < << >>
	char			*infile;
	char			*outfile;
	struct s_cmds	*next;
}	t_cmds;

char	*rl_gets (void);
t_cmds	*init_cmd(char **env);
char 	**get_env(char **envp);
void	parsing(t_cmds *cmd, char *line);
void 	free_arr(char **arr);
void	ft_error(int err);
void	free_cmd(t_cmds *cmd);

#endif