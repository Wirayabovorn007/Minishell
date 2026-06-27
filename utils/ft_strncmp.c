#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 0 && *s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str || fd < 0)
		return ;
	write(fd, str, ft_strlen(str));
}

int	pre_check_redir(t_cmd *cmd, t_token *next_tok, char *clean_val)
{
	if (cmd->redir_error)
	{
		free(clean_val);
		return (1);
	}
	if (next_tok->quote == NO_QUOTE && ft_strchr(next_tok->value, '*'))
	{
		cmd->ambiguous_redir = 1;
		cmd->ambig_target = clean_val;
		cmd->redir_error = 1;
		return (1);
	}
	return (0);
}

void	check_fd_error(t_cmd *cmd, int fd, char *val)
{
	if (fd < 0)
	{
		cmd->redir_error = 1;
		cmd->redir_errno = errno;
		cmd->redir_error_file = ft_strdup(val);
	}
	else
		close(fd);
}

void	apply_file_redir(t_cmd *cmd, char *val, int type)
{
	int	fd;

	if (type == APPEND)
		fd = open(val, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_OUT)
		fd = open(val, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(val, O_RDONLY);
	check_fd_error(cmd, fd, val);
	if (type == REDIR_IN)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = val;
	}
	else
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = val;
		cmd->append = (type == APPEND);
	}
}
