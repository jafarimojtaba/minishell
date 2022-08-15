/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:40 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/15 23:44:24 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	siginthandler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_clear_history();
	}
	else if (signum == SIGQUIT)
		printf("\b\b  \b\b");
}

void	signal_check(int argc, char **argv)
{
	if (argc || argv)
		argc = 2;
	signal(SIGINT, siginthandler);
	signal(SIGQUIT, siginthandler);
}

void	siginthandler_child(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_clear_history();
	}
	else if (signum == SIGQUIT)
		printf("\n");
}

void	signal_check_child()
{
	signal(SIGINT, siginthandler_child);
	signal(SIGQUIT, siginthandler_child);
}
