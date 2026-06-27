#include "minishell.h"

static void	add_arg(t_cmd *cmd, char *value)
{
	int		i;
	char	**new_argv;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i++] = ft_strdup(value);
	new_argv[i] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

void	handle_redir(t_cmd *cmd, t_token **tok, t_shell *shell)
{
	t_token	*next;
	char	*expanded;
	char	*val;

	next = (*tok)->next;
	if (cmd->redir_error)
	{
		*tok = next;
		return ;
	}
	expanded = expand_env(next->value, shell);
	val = remove_quotes(expanded);
	free(expanded);
	if (check_ambiguous(cmd, *tok, next, val))
	{
		*tok = next;
		return ;
	}
	set_redir_target(cmd, *tok, next, val);
	*tok = next;
}

static void	extract_and_add_arg(t_cmd *cmd, char *str, int start, int end)
{
	char	*word;
	char	*clean;

	word = ft_substr(str, start, end - start);
	clean = remove_quotes(word);
	add_arg(cmd, clean);
	free(word);
	free(clean);
}

void	split_and_add_args(t_cmd *cmd, char *str)
{
	int	i;
	int	start;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (!str[i])
			break ;
		start = i;
		skip_word(str, &i);
		extract_and_add_arg(cmd, str, start, i);
	}
}

t_cmd	*parse(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = NULL;
	current = new_cmd();
	add_cmd(&cmds, current);
	while (tokens)
	{
		process_token(&current, &cmds, &tokens, shell);
		tokens = tokens->next;
	}
	return (cmds);
}
