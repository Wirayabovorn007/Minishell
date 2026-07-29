#include "minishell.h"

int	builtin_pwd(t_shell *shell)
{
	char	cwd[4096];
	char	*logical_pwd;

	logical_pwd = get_env_val(shell->envp, "PWD");
	if (logical_pwd != NULL)
	{
		printf("%s\n", logical_pwd);
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
