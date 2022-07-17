/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/17 18:07:15 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *command_buff;

void print_split(char **sp)
{
	int i;

	i = 0;
	while (sp[i])
	{
		printf("%s\n", sp[i]);
		i++;
	}
}

int main(void)
{
	t_cmd *commands;

	int i = 0;
	int cmd_n;

	while (1)
	{
		command_buff = readline("MiniShell$ ");
		if (ft_strlen(command_buff) > 0)
			add_history(command_buff);
		// i = access("/bin/echo", R_OK);
		// cmd_n = cmd_num(command_buff);
		// not_closed_q(command_buff);
		cmd_n = cmd_count(command_buff);
		commands = (t_cmd *)malloc(cmd_n * sizeof(t_cmd));
		cmd_init(commands, cmd_n);
		ft_lexer(commands, command_buff);
		i = 0;
		while (i < cmd_n)
		{
			printf("PIPE_before = %d, PP_CMD : %s PIPE_after = %d$\n",commands[i].pipe_flag_before, commands[i].c_pre_parse, commands[i].pipe_flag_after);
			i++;
		}
		
		// cmd_c(commands,cmd_n);
		printf("ac = %d\n", cmd_n);
		// splitted = split_command(command_buff);
		// print_split(splitted);
	}
	return (0);
}
