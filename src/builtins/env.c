#include "minishell.h"

int	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (has_equal_sign(shell->envp[i]))
			printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
}
