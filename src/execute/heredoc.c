#include <minishell.h>

static void	handle_eof_or_sig(int *fd, char *delim, t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		close(fd[1]);
		free_and_exit(shell, 130);
	}
	printf("minishell: warning: here-document delimited "
		"by end-of-file (wanted `%s')\n", delim);
}

void	handle_heredoc_child(int *fd, char *delimiter, t_shell *shell)
{
	char	*line;

	close(fd[0]);
	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			handle_eof_or_sig(fd, delimiter, shell);
			break ;
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	free_and_exit(shell, 0);
}

int	handle_heredoc(char *delimiter, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) != 0)
	{
		perror("minishell: pipe");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(fd, delimiter, shell);
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
