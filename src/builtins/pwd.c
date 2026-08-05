#include "minishell.h"

int	builtin_pwd(t_shell *shell)
{
	char	cwd[4096];
	char	*prev_pwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	prev_pwd = get_env_val(shell->envp, "PWD");
	if (prev_pwd != NULL)
	{
		printf("%s\n", prev_pwd);
		return (0);
	}
	fprintf(stderr,
		"pwd: error retrieving current directory: "
		"getcwd: cannot access parent directories: "
		"No such file or directory\n");
	return (1);
}
