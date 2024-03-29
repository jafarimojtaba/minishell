/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/15 23:20:52 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_only_space(char *c, int i, int count)
{
	while (i < (int)ft_strlen(c))
	{
		if (c[i] != ' ' && c[i] != '\t')
			count++;
		i++;
	}
	return (count);
}

int	check_readline(char **cmd_buff, t_data *data)
{
	if (!*cmd_buff)
	{
		free_data(data);
		printf("\n");
		exit(1);
	}
	if (ft_strlen(*cmd_buff) > 0 && not_only_space(*cmd_buff, 0, 0))
	{
		add_history(*cmd_buff);
		return (1);
	}
	else
		return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd_buff;
	t_cmd	*cmd;
	t_data	*data;

	cmd_buff = NULL;
	signal_check(argc, argv);
	data = malloc(sizeof(t_data));
	data_init(data, env, cmd_buff);
	while (1)
	{
		cmd_buff = readline("MiniShell$ ");
		if (!check_readline(&cmd_buff, data))
			continue ;
		if (!is_q_closed(cmd_buff, 0))
		{
			printf("Please check your input for closed Quotes!\n");
			free(cmd_buff);
			continue ;
		}
		cmd = (t_cmd *)malloc(cmd_count(cmd_buff, 0, 1, data) * sizeof(t_cmd));
		minishell(&cmd_buff, cmd, data);
	}
	return (0);
}
