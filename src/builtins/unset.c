#include "minishell.h"

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;

	(void)shell;
	i = 1;
	while (argv[i])
	{
		printf("unset: %s\n", argv[i]);
		i++;
	}
	return (0);
}
