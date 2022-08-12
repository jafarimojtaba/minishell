/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:40 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 12:59:05 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	siginthandler(int signum)
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
		exit(1);
	}
	else if (signum == SIGSTOP)
	{
		exit(1);
	}
}

void	signal_check(int argc, char **argv)
{
	if (argc || argv)
		argc = 2;
	signal(SIGINT, siginthandler);
	signal(SIGQUIT, siginthandler);
	signal(SIGSTOP, siginthandler);
}
