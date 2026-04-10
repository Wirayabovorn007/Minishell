#include "minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		printf("You typed: %s\n", input);
		free(input);
	}
	return (0);
}