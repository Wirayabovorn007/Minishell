#include "minishell.h"

int	main(void)
{
	char	*input;
	char	*value;
	int		i;
	t_shell	shell;

	(void)shell;

	while ((input = readline("env_test$ ")))
	{
		i = 0;
		while (input[i])
		{
			if (input[i] == '$')
			{
				value = get_env_value(input, &shell, &i);
				printf("ENV VALUE: %s\n", value);
				free(value);
			}
			else
				i++;
		}
		free(input);
	}
	return (0);
}
