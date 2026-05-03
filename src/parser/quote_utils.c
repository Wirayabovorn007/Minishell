#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	has_unclosed_quote(char *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (!s[i])
				return (1);
		}
		i++;
	}
	return (0);
}
