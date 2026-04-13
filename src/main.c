#include "minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_token	*tmp;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		tmp = tokens;
		while (tmp)
		{
			printf("type: %d, value: %s\n", tmp->type, tmp->value);
			tmp = tmp->next;
		}
		free(input);
	}
	return (0);
}
