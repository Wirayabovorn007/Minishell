#include "minishell.h"

char	*get_word(char *s, int *i, int *quote)
{
	int	start;
	int	sq;
	int	dq;

	start = *i;
	sq = 0;
	dq = 0;
	*quote = NO_QUOTE;
	while (s[*i])
	{
		if (s[*i] == '\'' && !dq)
			sq = !sq;
		else if (s[*i] == '"' && !sq)
			dq = !dq;
		else if (!sq && !dq && (is_space(s[*i]) || is_operator(s[*i])))
			break ;
		(*i)++;
	}
	return (ft_substr(s, start, *i - start));
}
