#include "minishell.h"

int	builtin_exit(char **argv, t_shell *shell)
{
	(void)argv;
	(void)shell;
	printf("exit\n");
	exit(0);
}
