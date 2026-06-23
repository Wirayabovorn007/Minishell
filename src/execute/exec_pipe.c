
#include <minishell.h>



void	execute_pipe_child(int *fd, int *prev_fd, t_cmd *curr, t_shell *shell)
{
	char	*cmd_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	if (curr->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	if (setup_redirection(curr) != 0)
		exit(1);
	if (!curr->argv || !curr->argv[0])
		exit(0);
	if (is_builtin(curr->argv[0]))
		exit(exec_builtin(curr, shell, 1));
	cmd_path = get_cmd_path(curr->argv[0], shell->envp);
		if (!cmd_path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(curr->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		execve(cmd_path, curr->argv, shell->envp);
		perror("minishell: execve");
		free(cmd_path);
		exit(126);
}

void	execute_pipe_parent(int *prev_fd, t_cmd *curr, int *fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (curr->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

void	wait_result(pid_t pid, t_shell *shell)
{
	int		status;
	pid_t	wait_res;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while ((wait_res = waitpid(-1, &status, 0)) > 0)
	{
		if (wait_res == pid)
		{
			if (WIFEXITED(status))
				shell->last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				shell->last_exit_status = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					write(1, "Quit (core dumped)\n", 19);
				else if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
			}
		}
	}
	init_signals();
}

void	execute_pipe(t_cmd *cmds, t_shell *shell)
{
	int	fd[2];
	int	prev_fd;
	pid_t	pid;
	t_cmd	*curr;

	prev_fd = -1;
	curr = cmds;
	while (curr)
	{
		if (curr->next)
			pipe(fd);
		pid = fork();
		if (pid == 0)
			execute_pipe_child(fd, &prev_fd, curr, shell);
		else
			execute_pipe_parent(&prev_fd, curr, fd);
		curr = curr->next;
	}
	wait_result(pid, shell);
}
