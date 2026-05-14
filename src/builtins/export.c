#include "minishell.h"

int	builtin_export(char **argv, t_shell *shell)
{
	int	i;

	(void)shell;
	i = 1;
	while (argv[i])
	{
		printf("export: %s\n", argv[i]);
		i++;
	}
	return (0);
}
