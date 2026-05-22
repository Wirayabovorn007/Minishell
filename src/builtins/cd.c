#include "minishell.h"

static int	update_existing_env(t_shell *shell, char *key, char *str, int len)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key, len) == 0
			&& (shell->envp[i][len] == '=' || shell->envp[i][len] == '\0'))
		{
			free(shell->envp[i]);
			shell->envp[i] = str;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_new_env(t_shell *shell, char *new_str)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (shell->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (1);
	i = 0;
	while (shell->envp[i])
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	new_envp[i] = new_str;
	new_envp[i + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	return (0);
}

int	add_or_update_env(t_shell *shell, char *key, char *value)
{
	char	*new_str;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (1);
	if (value)
		new_str = ft_strjoin(temp, value);
	else
		new_str = ft_strdup(temp);
	free(temp);
	if (!new_str)
		return (1);
	if (!update_existing_env(shell, key, new_str, ft_strlen(key)))
	{
		if (add_new_env(shell, new_str))
			return (1);
	}
	return (0);
}

static int	update_dir_and_env(t_shell *shell, char *path)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		add_or_update_env(shell, "OLDPWD", cwd);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		add_or_update_env(shell, "PWD", cwd);
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*path;

	if (argv[1] && argv[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	if (!argv[1])
	{
		path = get_env_val(shell->envp, "HOME");
		if (!path)
		{
			write (2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else if (argv[1][0] == '\0')
	{
		write(2, "minishell: cd: : No such file or directory\n", 43);
		return (1);
	}
	else
		path = argv[1];
	return (update_dir_and_env(shell, path));
}
