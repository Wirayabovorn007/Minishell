#include "minishell.h"

int	is_single_builtin(t_cmd *cmds)
{
	if (!cmds || cmds->next)
		return (0);
	if (cmds->argv && cmds->argv[0] && is_builtin(cmds->argv[0]))
		return (1);
	return (0);
}

char *ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return NULL;
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	if (str[i] == c) 
		return str + i;
	return NULL;
}
