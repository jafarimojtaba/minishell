/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/09 08:00:47 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *cmd_buff;



int not_only_space(char *c, int i, int count)
{
	while (c[i] != '\0')
	{
		if (c[i] != ' ' && c[i] !='\t')
			count++;
		i++;
	}
	return(count);
}
int main(int argc, char **argv, char **env)
{
	char *cmd_buff;
	t_cmd *cmd;
	t_data *data;
	int cmd_n;

	// printf("path str:%s , path:%s\n", data->path_str, data->path);
	// signal_check();
	if (argc || argv)
		argc =2;
	data = calloc(1, sizeof(t_data));
	data_init(data, env);
	while (1)
	{
		exe_remove(env);
		// printf("path str:%s , path:%s\n", data->path_str, data->path);
		cmd_buff = readline("MiniShell$ ");
		if (ft_strlen(cmd_buff) > 0 && not_only_space(cmd_buff, 0, 0))
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
