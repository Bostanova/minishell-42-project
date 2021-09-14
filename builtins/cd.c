#include "../includes/minishell.h"

static void	change_env_pwd(t_env *env, char *pwd, char *oldpwd) {
	t_env *head;
	char *tmp;
	int sign;
	
	sign = 0;
	head = env;
	while (env) {
		if (!(ft_strcmp(env->name, "PWD"))) {
			tmp = env->data;
			env->data = ft_strdup(pwd);
			free(tmp);
		}
		else if (!(ft_strcmp(env->name, "OLDPWD"))) {
			tmp = env->data;
			env->data = ft_strdup(oldpwd);
			free(tmp);
			sign = 1;
		}
		env = env->next;
	}
	env = head;
	if (!sign)
		addelem(env, "OLDPWD", oldpwd);
}

void	cd_cmd(t_cmds *cmd, t_env *env) {
	char		*pwd;
	char		*oldpwd;
	struct stat	stats;

	oldpwd = getcwd(NULL, 0);
	if (stat(cmd->args[1], &stats) == 0) {
		chdir(cmd->args[1]);
		pwd = getcwd(NULL, 0);
		change_env_pwd(env, pwd, oldpwd);
		if (pwd)
			free(pwd);
	}
	else {
		if (errno) 
			printf ("minishell: cd: %s\n", strerror(errno));
	}
	if (oldpwd)
		free(oldpwd);
}
