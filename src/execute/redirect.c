
#include <minishell.h>

int setup_redirection(t_cmd *cmd)
{
	int	fd_in;
	int	fd_out;

	if (cmd->infile)
	{
		fd_in = open(cmd->infile, O_RDONLY);
		if (fd_in < 0) {
			perror(cmd->infile);
			return (1);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->outfile)
	{
		if (cmd->append == 1)
			fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644); // >>
		else
			fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); // >
		if (fd_out < 0)
		{
			perror(cmd->outfile);
			return (1);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (0);
}
