/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:22:29 by eerika            #+#    #+#             */
/*   Updated: 2021/10/05 19:30:46 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define PROMPT "minishell$ "
# define TRUE 1
# define GREAT 1
# define LESS 2
# define GREATGREAT 3
# define LESSLESS 4
# define SYNTAXERROR -1

int		g_exit;

typedef struct s_cmds
{
	char			**env;
	char			**args;
	int				count_args;
	int				pipe;
	int				redir[2];
	char			*infile;
	char			*outfile;
	struct s_cmds	*next;
}	t_cmds;

char	*rl_gets(void);
t_cmds	*init_cmd(char **env);
char	**get_array_of_env(char **envp);
int		parsing(t_cmds *cmd, char *line, char **env);
void	alloc_new_arg(t_cmds *cmd, char *line, int *i);
char	**global_alloc(char **arr, int size);
char	*add_char(char *str, char c);
int		is_new_arg(char c);
void	parse_cmd(t_cmds *cmd, char *line, int *i);
void	parse_single_quotes(t_cmds *cmd, char *line, int *i, int redir);
void	parse_double_quotes(t_cmds *cmd, char *line, int *i, int redir);
void	parse_env(t_cmds *cmd, char *line, int *i, int redir);
int		parse_redirect(t_cmds *cmd, char *line, int *i);
void	free_arr(char **arr);
void	ft_error(int err);
void	free_cmd(t_cmds *cmd);
void	pwd_cmd(void);
void	env_cmd(t_cmds *cmd);
void	cd_cmd(t_cmds *cmd, char ***env);
void	free_env(char ***env);
void	unset_cmd(t_cmds *cmd, char ***env);
void	error_unset(int nbr, char *err);
void	echo_cmd(t_cmds *cmd);
void	export_cmd(t_cmds *cmd, char ***env);
void	error_export(int nbr, char *err);
void	exit_cmd(t_cmds *cmd);
void	error_exit(int nbr, char *err);
void	execution(t_cmds *cmd, char ***env);
void	error_cmd_not_found(int nbr, char *err);
void	error_open_file(int nbr, char *err);
char	*test_path(char **path, char *cmd);
char	**get_path(char **env);
void	open_files(t_cmds *cmd, int *infile_fd, int *outfile_fd);
int		check_buildin(char *cmd);
void	exec_buildins(t_cmds *cmd, int outfile_fd, \
			char ***env, int stdin_initial);
void	exec_cmd(t_cmds *cmd, int isbuildin, char ***env);
void	go_to_buildin(t_cmds *cmd, char ***env);
void	error(int error);
void	handle_signals(void);
void	ignore_signals(void);
void	child_signals(int status);

void print_arr(char **arr); //remove later,  it's for checking
void print_cmd(t_cmds *cmd);

#endif