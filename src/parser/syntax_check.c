#include "minishell.h"

static int	is_redirection(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == APPEND
		|| type == HEREDOC);
}

static int	check_pipe(t_token *tok)
{
	if (tok->type == PIPE)
	{
		if (!tok->next || tok->next->type == PIPE)
		{
			printf("syntax error near unexpected token `|'\n");
			return (0);
		}
	}
	return (1);
}

static int	check_redirection(t_token *tok)
{
	if (is_redirection(tok->type))
	{
		if (!tok->next || tok->next->type != WORD)
		{
			printf("syntax error near unexpected token\n");
			return (0);
		}
	}
	return (1);
}

int	syntax_check(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (0);
	}
	while (tokens)
	{
		if (!check_pipe(tokens))
			return (0);
		if (!check_redirection(tokens))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
