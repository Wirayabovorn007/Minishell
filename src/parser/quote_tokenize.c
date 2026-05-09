#include "minishell.h"

static char	*quoted_word(char *s, int *i)
{
	char	quote;
	int		start;
	char	*word;

	quote = s[*i];
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	word = word_dup(s, start, *i);
	if (s[*i] == quote)
		(*i)++;
	return (word);
}

static char	*normal_word(char *s, int *i)
{
	int	start;

	start = *i;
	while (s[*i]
		&& !is_space(s[*i])
		&& !is_operator(s[*i])
		&& !is_quote(s[*i]))
		(*i)++;
	return (word_dup(s, start, *i));
}

char	*get_word(char *s, int *i)
{
	if (is_quote(s[*i]))
		return (quoted_word(s, i));
	return (normal_word(s, i));
}
