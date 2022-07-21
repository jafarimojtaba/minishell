/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/21 20:19:57 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *command_buff;

int main(void)
{
// char *command_buff;

	// t_com	*commands;
	// int		n_pipes;
	// argc = 0;
	// int fdd = 0;
	// argv = NULL;
	// char **splitted;
	// int i = 0;
	
	// buff = (char *)malloc(6 * sizeof(char));
	char *write_cmd[] = { "/bin/sh", "-c", "<a cat > b", NULL };
// ...
// execv("/bin/sh", write_cmd);
	char *argVec[] = {"cat", "a", ">", "b", NULL};
	char *enVec[] = {NULL};
	// ft_env(env);
	// while (i++ < 3)
	// {
		// command_buff = readline("minishell>");
		// if (ft_strlen(command_buff) > 0)
		// 	add_history(command_buff);
		// splitted = parser(command_buff);
		// // printf("command = %s\n", command_buff);
		// n_pipes = pipe_counter(splitted);
		// commands = (t_com *)malloc((n_pipes + 1) * sizeof(t_com));
		// search_commands(splitted, n_pipes, commands);
		// printf("pipes are = %d\n", n_pipes);
		// argVec[1] = command_buff;
		// dup2(fdd, STDOUT_FILENO);
		execve("/bin/sh" , write_cmd, enVec);
		// write(fdd, )
		// printf("%s",buff);
		// free_splitted(splitted);
	// }

	// command_buff = readline("minishell: ");
	// printf("%s", getenv("PATH"));
	return (0);
}