#include "minishell.h"

static int	env_name_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (is_alnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

char	*get_env_value(char *str, t_shell *shell, int *i)
{
	char	*name;
	char	*value;
	int		len;

	(void)shell;
	(*i)++;
	len = env_name_len(&str[*i]);
	name = ft_substr(str, *i, len);
	value = getenv(name);
	free(name);
	*i += len;
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
