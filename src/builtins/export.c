#include "minishell.h"

char	**copy_env(char **env)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (env_len(env) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static char	**add_env(char **env, char *new_var)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (env_len(env) + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

static void	update_env(char **env, int index, char *new_var)
{
	free(env[index]);
	env[index] = ft_strdup(new_var);
}

static int	handle_export_arg(char *arg, char ***env)
{
	int	index;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (1);
	}
	index = find_env(*env, arg);
	if (index >= 0)
	{
		if (has_equal_sign(arg))
			update_env(*env, index, arg);
	}
	else
		*env = add_env(*env, arg);
	return (0);
}

int	builtin_export(char **argv, char ***env)
{
	int	i;
	int	status;

	status = 0;
	if (!argv[1])
	{
		print_export(*env);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (handle_export_arg(argv[i], env) == 1)
			status = 1;
		i++;
	}
	return (status);
}
