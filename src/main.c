#include "minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
	t_cmd	*tmp;
	int		i;

	while ((input = readline("minishell$ ")))
	{
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		cmds = parse(tokens);
		tmp = cmds;
		while (tmp)
		{
			printf("CMD:\n");
			i = 0;
			while (tmp->argv && tmp->argv[i])
			{
				printf("arg[%d]: %s\n", i, tmp->argv[i]);
				i++;
			}
			if (tmp->outfile)
				printf("outfile: %s\n", tmp->outfile);
			if (tmp->infile)
				printf("infile: %s\n", tmp->infile);
			tmp = tmp->next;
		}
		free(input);
	}
	return (0);
}
