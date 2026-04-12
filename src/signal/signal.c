#include "minishell.h"


int	g_signal =0;

void	handle_sigint(int sig)
{
	g_signal = sig;

}

void	init_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	// ctrl+c sigint
	sigemptyset(&sa_int.sa_mask)
	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa_int, NULL);

	// ctrl+/ does nothing for Interactive mode only 
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}