#include "minishell.h"

void	free_and_exit(t_shell *shell, int status)
{
	if (shell->envp)
		free_envp(shell->envp);
	if (shell->active_cmds)
		free_cmds(shell->active_cmds);
	rl_clear_history();
	if (shell->saved_stdin != 1)
		close(shell->saved_stdin);
	if (shell->saved_stdout != 1)
		close(shell->saved_stdout);
	exit(status);
}
