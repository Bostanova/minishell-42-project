#include "../includes/minishell.h"

static int	get_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

void	here_doc(char *stophere)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_line(&line))
		{
			if (ft_strncmp(line, stophere, ft_strlen(stophere)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	open_files(t_cmds *cmd, int *infile_fd, int *outfile_fd){
	if (cmd->redir[0] == LESSLESS && cmd->infile)
		here_doc(cmd->infile);
	else if (cmd->redir[0] == LESS && cmd->infile) {
		*infile_fd = open(cmd->infile, O_RDONLY);
		if (*infile_fd == -1)
			error_open_file(-1, cmd->infile);
		dup2(*infile_fd, STDIN_FILENO);
		close(*infile_fd);
	}
	if (cmd->redir[1] == GREATGREAT && cmd->outfile) {
		*outfile_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (*outfile_fd == -1)
			error_open_file(-1, cmd->outfile);
	}
	else if (cmd->redir[1] == GREAT && cmd->outfile) {
		*outfile_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (*outfile_fd == -1)
			error_open_file(-1, cmd->outfile);
	}
}