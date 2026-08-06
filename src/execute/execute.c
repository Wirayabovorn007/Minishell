#include <minishell.h>

void	print_err(t_cmd *cmd, int err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(err), 2);
	ft_putstr_fd("\n", 2);
}

void	handle_cmd_child(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	if (setup_redirection(cmd, shell) != 0)
	{
		if (shell->last_exit_status > 128)
			free_and_exit(shell, shell->last_exit_status);
		free_and_exit(shell, 1);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd->argv || !cmd->argv[0])
		free_and_exit(shell, 0);
	if (is_builtin(cmd->argv[0]))
		free_and_exit(shell, exec_builtin(cmd, shell, 1));
	cmd_path = get_cmd_path(cmd->argv[0], shell->envp);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_and_exit(shell, 127);
	}
	execve(cmd_path, cmd->argv, shell->envp);
	handle_exec_error(cmd, shell, cmd_path, errno);
}

void	handle_cmd_parent(t_shell *shell, pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->last_exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
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
	if (!cmds)
		return ;
	if (is_single_builtin(cmds))
	{
		shell->saved_stdin = dup(STDIN_FILENO);
		shell->saved_stdout = dup(STDOUT_FILENO);
		if (setup_redirection(cmds, shell) == 0)
			shell->last_exit_status = exec_builtin(cmds, shell, 1);
		else
			shell->last_exit_status = 1;
		dup2(shell->saved_stdin, STDIN_FILENO);
		dup2(shell->saved_stdout, STDOUT_FILENO);
		close(shell->saved_stdin);
		close(shell->saved_stdout);
		shell->saved_stdin = -1;
		shell->saved_stdout = -1;
	}
	else if (!cmds->next)
		execute_single_cmd(cmds, shell);
	else
		execute_pipe(cmds, shell);
}
