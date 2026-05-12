#include "minishell.h"

static int	is_env_char(char c)
{
	return (is_alnum(c) || c == '_');
}

char	*get_env_value(char *str, t_shell *shell, int *i)
{
	char	*name;
	char	*value;
	int		len;

	(void)shell;
	(*i)++;
	len = 0;
	while (str[*i + len] && is_env_char(str[*i + len]))
		len++;
	name = ft_substr(str, *i, len);
	value = getenv(name);
	free(name);
	*i += len;
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
