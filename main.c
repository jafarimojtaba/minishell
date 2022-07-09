/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/09 17:50:05 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

char *command_buff;

int main(void)
{
	char *argVec[] = {"echo", "hi how?", NULL};
	char *enVec[] = {NULL};
	// while (1)
	// {
		command_buff = readline("minishell>");
		argVec[1] = command_buff;
		execve("/bin/echo" , argVec, enVec);
	// }

	// command_buff = readline("minishell: ");
	// printf("%s", getenv("PATH"));

	return (0);
}