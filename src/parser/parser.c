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

static void	handle_redir(t_cmd *cmd, t_token **tok)
{
	if ((*tok)->type == REDIR_OUT)
		cmd->outfile = ft_strdup((*tok)->next->value);
	else if ((*tok)->type == APPEND)
	{
		cmd->outfile = ft_strdup((*tok)->next->value);
		cmd->append = 1;
	}
	else if ((*tok)->type == REDIR_IN)
		cmd->infile = ft_strdup((*tok)->next->value);
	else if ((*tok)->type == HEREDOC)
	{
		cmd->delimiter = ft_strdup((*tok)->next->value);
		cmd->heredoc = 1;
	}
	*tok = (*tok)->next;
}

static void	process_token(t_cmd **current, t_cmd **cmds, t_token **tok)
{
	if ((*tok)->type == WORD)
		add_arg(*current, (*tok)->value);
	else if ((*tok)->type == PIPE)
	{
		*current = new_cmd();
		add_cmd(cmds, *current);
	}
	else
		handle_redir(*current, tok);
}

t_cmd	*parse(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current;

	cmds = NULL;
	current = new_cmd();
	add_cmd(&cmds, current);
	while (tokens)
	{
		process_token(&current, &cmds, &tokens);
		tokens = tokens->next;
	}
	return (cmds);
}
