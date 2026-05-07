#include "minishell.h"

int	main(void)
{
	char	*input;
	char	*expanded;
	t_shell	shell;

	while ((input = readline("expand_test$ ")))
	{
		expanded = expand_env(input, &shell);
		printf("expanded: %s\n", expanded);
		free(expanded);
		free(input);
	}
	return (0);
}
