#include "minishell.h"

int	main(void)
{
	char	*input;
	t_token *tokens;

	while ((input = readline("minishell$ ")))
	{
		tokens = tokenize(input);
		if (syntax_check(tokens))
			printf("syntax ok\n");
		free_tokens(tokens);
		free(input);
	}
	return (0);
}
