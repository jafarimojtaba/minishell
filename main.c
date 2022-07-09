/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/09 19:42:28 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

char *command_buff;

int main(void)
{
	// argc = 0;
	int fdd = 0;
	// argv = NULL;
	char *buff;
	
	buff = (char *)malloc(6 * sizeof(char));
	char *argVec[] = {"echo", "ehsan", NULL};
	char *enVec[] = {NULL};
	// ft_env(env);
	// while (1)
	// {
		command_buff = readline("minishell>");
		// argVec[1] = command_buff;
		dup(fdd, STDOUT_FILENO);
		execve("/bin/echo" , argVec, enVec);
		read(fdd, buff, 5);
		printf("%s",buff);
	// }

	// command_buff = readline("minishell: ");
	// printf("%s", getenv("PATH"));

	return (0);
}