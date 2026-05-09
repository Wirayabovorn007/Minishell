#include "minishell.h"

static void print_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmds;
	while (tmp)
	{
		printf("CMD:\n");
		i = 0;
		while (tmp->argv && tmp->argv[i])
		{
			printf("argv[%d]: %s\n", i, tmp->argv[i]);
			i++;
		}
		if (tmp->infile)
			printf("infile: %s\n", tmp->infile);
		if (tmp->outfile)
			printf("outfile: %s\n", tmp->outfile);
		if (tmp->append)
			printf("append mode\n");
		if (tmp->heredoc)
			printf("heredoc: %s\n", tmp->delimiter);
		tmp = tmp->next;
	}
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
	t_shell	shell;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break;
		if (*input)
			add_history(input);
		if (has_unclosed_quote(input))
		{
			printf("unclosed quote\n");
			free(input);
			continue;
		}
		tokens = tokenize(input);
		if (!syntax_check(tokens))
		{
			free_tokens(tokens);
			free(input);
			continue;
		}
		cmds = parse(tokens, &shell);
		print_cmds(cmds);
		free_tokens(tokens);
		free_cmds(cmds);
		free(input);
	}
	return (0);
}
