#include "minishell.h"

void sigintHandler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\b\b  \n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_clear_history();
	}
	else if (signum == SIGQUIT)
	{
		printf("\b\b  \b\b");
		// exit(1);
	}
	else if (signum == SIGSTOP)
	{
		exit(1);
	}
}

void signal_check()
{
	signal(SIGINT, sigintHandler);
	signal(SIGQUIT, sigintHandler);
	signal(SIGSTOP, sigintHandler);
}