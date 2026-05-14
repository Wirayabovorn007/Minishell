#include "minishell.h"

int	main(void)
{
	char	*argv[2];
	t_shell	shell;

	argv[0] = "exit";
	argv[1] = NULL;
	printf("before exit\n");
	builtin_exit(argv, &shell);
	printf("after exit\n");
	return (0);
}
