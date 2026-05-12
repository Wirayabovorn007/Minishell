#include "minishell.h"

static char	*expand_exit_status(t_shell *shell)
{
	return (ft_itoa(shell->last_exit_status));
}

static int	update_quotes(char c, int *sq, int *dq)
{
	if (c == '\'' && !(*dq))
	{
		*sq = !(*sq);
		return (1);
	}
	else if (c == '"' && !(*sq))
	{
		*dq = !(*dq);
		return (1);
	}
	return (0);
}

static char	*handle_dollar(char *str, int *i, t_shell *shell)
{
	char	*tmp;

	if (str[*i + 1] == '?')
	{
		tmp = expand_exit_status(shell);
		*i += 2;
	}
	else if (str[*i + 1] && (is_alpha(str[*i + 1]) || str[*i + 1] == '_'))
		tmp = get_env_value(str, shell, i);
	else
	{
		tmp = ft_substr(str, *i, 1);
		(*i)++;
	}
	return (tmp);
}

char	*expand_env(char *str, t_shell *shell)
{
	char	*res;
	char	*tmp;
	int		i;
	int		sq;
	int		dq;

	res = ft_strdup("");
	i = 0;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (update_quotes(str[i], &sq, &dq) || str[i] != '$' || sq)
			tmp = ft_substr(str, i++, 1);
		else
			tmp = handle_dollar(str, &i, shell);
		res = join_and_free(res, tmp);
	}
	return (res);
}
