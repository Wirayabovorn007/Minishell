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

char	*remove_quotes(char *s)
{
	char	*res;
	int		i;
	int		j;
	int		in_squote;
	int		in_dquote;

	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (s[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	skip_word(char *str, int *i)
{
	int	in_sq;
	int	in_dq;

	in_sq = 0;
	in_dq = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (str[*i] == '"' && !in_sq)
			in_dq = !in_dq;
		else if (is_space(str[*i]) && !in_sq && !in_dq)
			break ;
		(*i)++;
	}
}
