#include "minishell.h"

t_token	*new_token(char *value, t_token_type type, int quote)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->quote = quote;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	process_token(t_cmd **cur, t_cmd **cmd, t_token **t, t_shell *sh)
{
	char	*expanded;

	if ((*t)->type == WORD)
	{
		expanded = expand_env((*t)->value, sh);
		split_and_add_args(*cur, expanded);
		free(expanded);
	}
	else if ((*t)->type == PIPE)
	{
		*cur = new_cmd();
		add_cmd(cmd, *cur);
	}
	else
		handle_redir(*cur, t, sh);
}

void	test_file_access(t_cmd *cmd, t_token *tok, char *val)
{
	int	fd;

	fd = 0;
	if (tok->type == REDIR_IN)
		fd = open(val, O_RDONLY);
	else if (tok->type == REDIR_OUT)
		fd = open(val, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tok->type == APPEND)
		fd = open(val, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		cmd->redir_error = 1;
		cmd->redir_errno = errno;
		cmd->redir_error_file = ft_strdup(val);
	}
	else if (fd > 0)
		close(fd);
}
