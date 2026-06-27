
#include "minishell.h"

int	check_ambiguous(t_cmd *cmd, t_token *tok, t_token *next, char *val)
{
	if (next->quote == NO_QUOTE && ft_strchr(next->value, '$')
		&& (val[0] == '\0' || ft_strchr(val, ' ')))
	{
		cmd->ambiguous_redir = 1;
		cmd->ambig_target = ft_strdup(next->value);
		cmd->redir_error = 1;
		free(val);
		return (1);
	}
	if (tok->type != HEREDOC && next->quote == NO_QUOTE
		&& ft_strchr(next->value, '*'))
	{
		cmd->ambiguous_redir = 1;
		cmd->ambig_target = val;
		cmd->redir_error = 1;
		return (1);
	}
	return (0);
}

void	set_redir_target(t_cmd *cmd, t_token *tok, t_token *next, char *val)
{
	if (tok->type == HEREDOC)
	{
		cmd->delimiter = remove_quotes(next->value);
		free(val);
		cmd->heredoc = 1;
		if (next->quote != NO_QUOTE)
			cmd->heredoc_quoted = 1;
	}
	else
		apply_file_redir(cmd, val, tok->type);
}
