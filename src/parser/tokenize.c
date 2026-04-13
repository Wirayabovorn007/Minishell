#include "minishell.h"

static int	handle_pipe(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|')
	{
		add_token(tokens, new_token("|", PIPE));
		(*i)++;
		return (1);
	}
	return (0);
}

static int	handle_redir_out(char *input, int *i, t_token **tok)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			add_token(tok, new_token(">>", APPEND));
			*i += 2;
		}
		else
		{
			add_token(tok, new_token(">", REDIR_OUT));
			(*i)++;
		}
		return (1);
	}
	return (0);
}

static int	handle_redir_in(char *input, int *i, t_token **tok)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			add_token(tok, new_token("<<", HEREDOC));
			*i += 2;
		}
		else
		{
			add_token(tok, new_token("<", REDIR_IN));
			(*i)++;
		}
		return (1);
	}
	return (0);
}

static void	handle_word(char *input, int *i, t_token **tokens)
{
	char	*word;

	word = get_word(input, i);
	add_token(tokens, new_token(word, WORD));
	free(word);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (handle_pipe(input, &i, &tokens))
			continue ;
		else if (handle_redir_out(input, &i, &tokens))
			continue ;
		else if (handle_redir_in(input, &i, &tokens))
			continue ;
		else
			handle_word(input, &i, &tokens);
	}
	return (tokens);
}
