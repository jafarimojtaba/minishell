/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/24 11:40:50 by mjafari          ###   ########.fr       */
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
	t_cmd	*cmd;
	char	*cmd_buff;
	int		cmd_n;
	int		i;

	while (1)
	{
		cmd_buff = readline("MiniShell$ ");
		if (ft_strlen(cmd_buff) > 0)
			add_history(cmd_buff);
		if (!is_q_closed(cmd_buff, 0))
		{
			printf("Please check your input for closed Quote/s\n!");
			continue;
		}
		cmd_n = cmd_count(cmd_buff, 0, 1);
		cmd = (t_cmd *)malloc(cmd_n * sizeof(t_cmd));
		cmd_init(cmd, cmd_n);
		ft_lexer(cmd, command_buff);
		ft_input_replace(cmd);
		ft_dollar_replace(cmd);
		ft_dollar_no_q(cmd);
		ft_redirection(cmd, 0);
		// ft_lexer2(commands, commands->c_pre_parse);
		// i = 0;
		// while (i < cmd_n)
		// {
		// 	// printf("PIPE_before = %d, PIPE_after = %d PP_CMD : %s$\n",commands[i].pipe_flag_before, commands[i].pipe_flag_after, commands[i].c_pre_parse);
		// 	printf("PP_CMD_re:%s#\n", commands[i].c_pre_parse);
		// 	// printf("CMD_re:%s#\n", commands[i].c);
		// 	i++;
		// }
		cmd_c(cmd,cmd_n);
		args_selector(cmd, cmd_n);
		i = 0;
		while (i < cmd_n)
		{
			// printf("PIPE_before = %d, PIPE_after = %d PP_CMD : %s$\n",commands[i].pipe_flag_before, commands[i].pipe_flag_after, commands[i].c_pre_parse);
			printf("PP_CMD:%s#\n", cmd[i].c_pre_parse);
			// printf("CMD:%s#\n", commands[i].c);
			i++;
		}

		// printf("ac = %d\n", cmd_n);
		// splitted = split_command(command_buff);
		// print_split(splitted);
	}
	return (0);
}
//<f0 echo hi >f1 how >f2 >f3 are you >f4
// echo hi  how   are you 
//  echo hi  how   are you 
//   echo hi  how   are you 
// <f0 echo hi >f1 how >f2 >f3 are you >f4 |>f7 >f8 grep hi <f9
//echo hi how are you|grep hi
//<f0 echo hi >f1 how >f2 >f3 are you  >f4 |>f7 >f8 grep hi <f9 "hh$USER" << mj to