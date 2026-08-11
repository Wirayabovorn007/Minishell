#include "minishell.h"

void	free_and_exit(t_shell *shell, int status)
{
	if (shell->envp)
		free_envp(shell->envp);
	if (shell->active_cmds)
		free_cmds(shell->active_cmds);
	rl_clear_history();
	if (shell->saved_stdin != -1)
		close(shell->saved_stdin);
	if (shell->saved_stdout != -1)
		close(shell->saved_stdout);
	exit(status);
}

int	print_cd_err(void)
{
	write(2, "minishell: cd: : No such file or directory\n", 43);
	return (1);
}

int	special_cd(char **argv, t_shell *shell, char **path, int *is_allocated)
{
	if (ft_strcmp(argv[1], "-") == 0)
	{
		*path = get_cd_path(argv, shell);
		if (!*path)
			return (1);
	}
	else if (ft_strcmp(argv[1], "~") == 0)
	{
		*path = get_env_val(shell->envp, "HOME");
		if (!*path)
			return (1);
	}
	else if (argv[1][0] == '~' && argv[1][1] == '/')
	{
		*path = get_env_val(shell->envp, "HOME");
		if (!*path)
			return (1);
		*path = ft_strjoin(*path, argv[1] + 1);
		*is_allocated = 1;
	}
	else if (argv[1][0] == '\0')
		print_cd_err();
	else
		*path = argv[1];
	return (0);
}
