#include "minishell.h"

char	*expand_env(char *str, t_shell *shell)
{
	char	*res;
	char	*tmp;
	char	*new_res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			tmp = get_env_value(str, shell, &i);
		else
			tmp = ft_substr(str, i++, 1);
		new_res = ft_strjoin(res, tmp);
		free(res);
		free(tmp);
		res = new_res;
	}
	return (res);
}
