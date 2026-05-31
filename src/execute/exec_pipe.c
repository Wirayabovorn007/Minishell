
#include "minishell.h"

void execute_pipe(t_cmd *cmds, t_shell *shell)
{
	int	fd[2];
	int	prev_fd;
	pid_t	pid;
	int		status;
	t_cmd	*curr;
	char	*cmd_path;

	prev_fd = -1;
	curr = cmds;
	while (curr)
	{
		if (curr->next)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (curr->next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			if (setup_redirection(curr) != 0)
				exit(1);
			if (is_builtin(curr->argv[0]))
				exit(exec_builtin(curr, shell, 1));
			else
			{
				cmd_path = get_cmd_path(curr->argv[0], shell->envp);
				if (!cmd_path)
				{
					printf("minishell: \n%s: command not found\n", cmds->argv[0]);
					exit(127);
				}
				execve(cmd_path, curr->argv, shell->envp);
				exit(126);
			}
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (curr->next)
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
		}
		curr = curr->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
}

