
#include <minishell.h>


void	handle_cmd_child(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (setup_redirection(cmd) != 0)
		exit(1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(cmd, shell, 1));
	else
	{
		cmd_path = get_cmd_path(cmd->argv[0], shell->envp);
		if (!cmd_path)
		{
			printf("minishell: \n%s: command not found\n", cmd->argv[0]);
			exit(127);
		}
		execve(cmd_path, cmd->argv, shell->envp);
		perror("minishell: execve");
		free(cmd_path);
		exit(126);
	}
}

void	handle_cmd_parent(t_shell *shell, pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFEXITED(status))
		shell->last_exit_status = WIFEXITED(status);
	else if (WIFSIGNALED(status))
	{
		shell->last_exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
	}
}

void	execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		handle_cmd_child(cmd, shell);
	else
		handle_cmd_parent(shell, pid);
}

void	execute(t_cmd *cmds, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!cmds)
		return ;
	if (is_single_builtin(cmds))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (setup_redirection(cmds) == 0)
			shell->last_exit_status = exec_builtin(cmds, shell, 1);
		else
			shell->last_exit_status = 1;
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	} 
	else if (!cmds->next)
		execute_single_cmd(cmds, shell);
	else
		execute_pipe(cmds, shell);
}
