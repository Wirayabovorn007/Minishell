#include "minishell.h"

static char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*helper(char **paths, char *path)
{
	free(paths);
	return (path);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!get_env_path(envp))
		return (NULL);
	paths = ft_split(get_env_path(envp), ':');
	i = -1;
	while (paths && paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			helper(paths, path);
		free(path);
	}
	free_arr(paths);
	return (NULL);
}
