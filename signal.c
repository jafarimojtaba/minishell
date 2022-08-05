#include "minishell.h"

void sigintHandler(int signum)
{
if (signum == SIGINT)
	{
		printf("\b\b  \n");
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		printf("\b\b  \b\b");
}

void signal_check()
{
	signal(SIGINT, sigintHandler);
}