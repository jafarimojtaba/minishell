/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/04 18:47:37 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *cmd_buff;

void print_cmd(t_cmd *cmd, int n)
{
	int i = 0;
	int j;
	printf("in print cmd%d", n);
	while (i < n)
	{
		// printf("PIPE_before = %d, PIPE_after = %d PP_CMD : %s$\n",commands[i].pipe_flag_before, commands[i].pipe_flag_after, commands[i].c_pre_parse);
		puts("------------------------------------------------");
		printf("CMD_PP:%s#\n", cmd[i].c_pre_parse);
		printf("CMD:%s#\n", cmd[i].c);
		puts("");
		j = 0;
		while (j < cmd[i].op_n)
		{
			printf("op %d=%s#\n", j, cmd[i].op[j]);
			j++;
		}
		puts("");
		j = 0;
		while (j < cmd[i].re_n)
		{
			printf("re %d=\ttype=%d\tfname=%s\tstr=%s#\n", cmd[i].re[j].id, cmd[i].re[j].type, cmd[i].re[j].f_name, cmd[i].re[j].str);
			j++;
		}
		puts("");
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	char *cmd_buff;
	t_cmd *cmd;
	t_data *data;
	int cmd_n;

	// printf("path str:%s , path:%s\n", data->path_str, data->path);
	// signal_check();
	data = calloc(1, sizeof(t_data));
	data_init(data);
	while (1)
	{
		if (argc || argv)
			exe_remove(data, env);
		// printf("path str:%s , path:%s\n", data->path_str, data->path);
		cmd_buff = readline("MiniShell$ ");
		if (ft_strlen(cmd_buff) > 0)
			add_history(cmd_buff);
		else
			continue;
		if (!is_q_closed(cmd_buff, 0))
		{
			printf("Please check your input for closed Quotes!\n");
			continue;
		}
		cmd_n = cmd_count(cmd_buff, 0, 1);
		cmd = (t_cmd *)calloc(cmd_n, sizeof(t_cmd));
		cmd->cmd_n = cmd_n;
		minishell(cmd_buff, cmd, data, env);
	}
	return (0);
}
