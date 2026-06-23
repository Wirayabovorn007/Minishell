#include <minishell.h>

int	check_heredoc(t_cmd *cmd, int *fd_in)
{
	if (!cmd->delimiter)
		return (0);
	*fd_in = handle_heredoc(cmd->delimiter);
	if (*fd_in < 0)
		return (1);
	dup2(*fd_in, STDIN_FILENO);
	close(*fd_in);
	return (0);
}

int check_input(t_cmd *cmd, int *fd_in)
{
	if (!cmd->infile)
		return (0);
	*fd_in = open(cmd->infile, O_RDONLY);
	if (*fd_in < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->infile, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	dup2(*fd_in, STDIN_FILENO);
	close(*fd_in);
	return (0);
}

int check_output(t_cmd *cmd, int *fd_out)
{
	if (!cmd->outfile)
		return (0);
	if (cmd->append == 1)
		*fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->outfile, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	dup2(*fd_out, STDOUT_FILENO);
	close(*fd_out);
	return (0);
}

int	setup_redirection(t_cmd *cmd)
{
	int	fd_in;
	int	fd_out;

	if (cmd->ambiguous_redir)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->ambig_target, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (1);
	}
	if (check_heredoc(cmd, &fd_in) != 0)
		return (1);
	else if (check_input(cmd, &fd_in) != 0)
		return (1);
	if (check_output(cmd, &fd_out) != 0)
		return (1);
	return (0);
}
