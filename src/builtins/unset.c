#include "minishell.h"

static void	print_unset_error(char *arg)
{
	write(2, "minishell: unset: `", 19);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

static int	is_valid_unset_id(char *str)
{
	int	i;

	if (!str || (!is_alpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!is_alnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	match_env(char *env, char *key)
{
	int	i;

	i = 0;
	while (key[i] && env[i] && key[i] == env[i])
		i++;
	if (key[i] == '\0' && (env[i] == '=' || env[i] == '\0'))
		return (1);
	return (0);
}

static void	unset_one(char *key, t_shell *shell)
{
	int	j;

	j = 0;
	while (shell->envp[j])
	{
		if (match_env(shell->envp[j], key))
		{
			free(shell->envp[j]);
			while (shell->envp[j])
			{
				shell->envp[j] = shell->envp[j + 1];
				j++;
			}
			break ;
		}
		j++;
	}
}

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!is_valid_unset_id(argv[i]))
			print_unset_error(argv[i]);
		else
			unset_one(argv[i], shell);
		i++;
	}
	return (0);
}
