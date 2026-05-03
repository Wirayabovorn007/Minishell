#include "minishell.h"

int	main(void)
{
	char	*input;

	while ((input = readline("minishell$ ")))
	{
		if (has_unclosed_quote(input))
			printf("unclosed quote\n");
		else
			printf("quote ok\n");
		free(input);
	}
	return (0);
}
