#include "minishell.h"

void	print_export(char **env)
{
	int		i;
	int		j;
	char	**copy;

	copy = copy_env(env);
	if (!copy)
		return ;
	sort_env(copy);
	i = 0;
	while (copy[i])
	{
		j = 0;
		while (copy[i][j] && copy[i][j] != '=')
			j++;
		if (copy[i][j] == '=')
			printf("declare -x %.*s=\"%s\"\n", j, copy[i], copy[i] + j + 1);
		else
			printf("declare -x %s\n", copy[i]);
		i++;
	}
	free_arr(copy);
}

void	print_export_error(char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

int	has_equal_sign(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
