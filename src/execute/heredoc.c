
#include "minishell.h"

void	show_warn(char *delimiter, char *cmd)
{
	if (strcmp(cmd, "echo") == 0)
		printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
}


int	handle_heredoc(t_cmd *cmd)
{
	int	fd[2];
	pid_t	pid;
	char *line;
	int	status;
	char *delimiter;

	delimiter = cmd->delimiter;
	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		return -1;
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				show_warn(delimiter, cmd->argv[0]);
				break ;
			}
			if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
				&& ft_strlen(line) == ft_strlen(delimiter))
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
