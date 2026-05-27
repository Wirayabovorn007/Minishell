
#include <minishell.h>


void	execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (setup_redirection(cmd) != 0)
			exit(1);
		if (is_builtin(cmd->argv[0]))
			exit(exec_builtin(cmd, shell, 1));
		else
		{
			printf("minishell: \n%s: command not found\n", cmd->argv[0]);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
	}
}


void	execute(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return ;
	if (is_single_builtin(cmds))
		shell->last_exit_status = exec_builtin(cmds, shell, 1);
	else if (!cmds->next)
		execute_single_cmd(cmds, shell);
	// else
	// {
	//  execute_pipes()
	// }
}
