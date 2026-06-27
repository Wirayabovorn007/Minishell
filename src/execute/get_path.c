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

char	*search_paths(char **paths, char *cmd)
{
	char	*path;
	char	*part;
	int		i;

	i = -1;
	while (paths && paths[++i])
	{
		part = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part, cmd);
		free(part);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!get_env_path(envp))
		return (NULL);
	paths = ft_split(get_env_path(envp), ':');
	path = search_paths(paths, cmd);
	free_arr(paths);
	return (path);
}
