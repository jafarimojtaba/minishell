/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 11:16:20 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/03 17:36:59 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cmd_init(t_cmd *cmd, char *cmd_buff, int n, char **env)
{
	int i;

	i = 0;
	while (i < n)
	{
		cmd[i].id = i;
		cmd[i].c_buf = cmd_buff;
		cmd[i].cmd_n = n;
		cmd[i].op_n = 0;
		cmd[i].pipe_flag_before = -1;
		cmd[i].pipe_flag_after = -1;
		cmd[i].pipe_f_name = ft_strjoin("mini_temp_pipe_", ft_itoa(i));
		cmd[i].fd_in = 0;
		cmd[i].fd_out = 1;
		cmd[i].re_n = 0;
		cmd[i].heredoc_id = -1;
		cmd[i].env = env;
		if (i)
			cmd[i].data = cmd[0].data;
		i++;
	}
}

int is_q_closed(char *c, int i)
{
	while (c[i])
	{
		if (c[i] == '\'' || c[i] == '"')
		{
			i = find_next_q(c, c[i], i);
			if (!i)
				return(0);
		}
		i++;
	}
	return(1);
}

int	cmd_count(char *c, int i, int count)
{
	// printf("size = %zu, c in counter=%s\n", ft_strlen(c), &c[i]);
	while (c[i])
	{
		if (c[i] == '\'' || c[i] == '"')
			i = find_next_q(c, c[i], i);
		else if (c[i] == '|' && c[i + 1])
		{
			i++;
			while (c[i] == ' ')
				i++;
			if (c[i])
				count++;
			continue;
		}
		i++;
	}
	return (count);
}
