#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!is_alpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!is_alnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	find_env(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (key[len] && key[len] != '=')
		len++;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len)
			&& (env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	sort_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
				swap(&env[i], &env[j]);
			j++;
		}
		i++;
	}
}
