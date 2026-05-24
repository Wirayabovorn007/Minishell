#include "minishell.h"

extern int g_signal;

// static void	run_test_cmd(t_cmd *cmds, t_shell *shell)
// {
// 	if (cmds && cmds->argv && cmds->argv[0])
// 	{
// 		if (is_builtin(cmds->argv[0]))
// 			shell->last_exit_status = exec_builtin(cmds, shell, 1);
// 		else
// 		{
// 			printf("minishell: %s: command not found\n", cmds->argv[0]);
// 			shell->last_exit_status = 127;
// 		}
// 	}
// }

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
	if (!syntax_check(tokens))
	{
		shell->last_exit_status = 2;
		free_tokens(tokens);
		return ;
	}
	cmds = parse(tokens, shell);
	free_tokens(tokens);
	// run_test_cmd(cmds, shell);
	free_cmds(cmds);
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
	if (init_env(&shell, envp) != 0)
	{
		write(2, "minishell: Error initializing environment\n", 42);
		return (1);
	}
	init_signals();
	shell_loop(&shell);
	free_envp(shell.envp);
	rl_clear_history();
	return (shell.last_exit_status);
}

// ตัวแปร cmds ที่โยนเข้า Execute
// cmds->argv = อาร์เรย์ของคำสั่งและ flag (เช่น ["ls", "-l", NULL])

// cmds->infile / cmds->outfile = ชื่อไฟล์ที่ต้องทำ Redirect (ถ้าไม่มีจะเป็น NULL)

// cmds->append = เป็น 1 ถ้าเจอ >>

// cmds->heredoc = เป็น 1 ถ้าเจอ << (พร้อม delimiter)

// cmds->next = ชี้ไปที่คำสั่งถัดไปถ้ามีการทำ Pipe |