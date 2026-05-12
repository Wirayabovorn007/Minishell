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
		handle_redir(*cur, t);
}
