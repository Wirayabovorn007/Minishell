#include "minishell.h"

extern int	g_signal;

static void	process_input(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (has_unclosed_quote(line))
	{
		write(2, "minishell: syntax error: unclosed quotes\n", 41);
		shell->last_exit_status = 2;
		return ;
	}
	tokens = tokenize(line);
	if (!tokens)
		return ;
	if (!syntax_check(tokens))
	{
		shell->last_exit_status = 2;
		free_tokens(tokens);
		tokens = NULL;
		return ;
	}
	cmds = parse(tokens, shell);
	shell->active_cmds = cmds;
	free_tokens(tokens);
	execute(cmds, shell);
	free_cmds(cmds);
	shell->active_cmds = NULL;
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*line)
		{
			add_history(line);
			process_input(line, shell);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.last_exit_status = 0;
	shell.active_cmds = NULL;
	shell.saved_stdin = -1;
	shell.saved_stdout = -1;
	if (init_env(&shell, envp) != 0)
	{
		write(2, "minishell: Error initializing environment\n", 42);
		return (1);
	}
	init_signals();
	shell_loop(&shell);
	free_envp(shell.envp);
	rl_clear_history();
	if (shell.saved_stdin != -1)
		close(shell.saved_stdin);
	if (shell.saved_stdout != -1)
		close(shell.saved_stdout);
	return (shell.last_exit_status);
}
