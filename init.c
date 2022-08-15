/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 11:16:20 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/15 23:15:11 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_init(t_cmd *cmd, t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < data->cmd_n)
	{
		cmd[i].id = i;
		cmd[i].c_pre_parse = NULL;
		cmd[i].c = NULL;
		cmd[i].c_path = NULL;
		cmd[i].op_n = 0;
		cmd[i].op = NULL;
		cmd[i].pipe_flag_before = -1;
		cmd[i].pipe_flag_after = -1;
		temp = ft_itoa(i);
		cmd[i].pipe_f_name = ft_strjoin("mini_temp_pipe_", temp);
		free(temp);
		cmd[i].fd_in = 0;
		cmd[i].fd_out = 1;
		cmd[i].re_n = 0;
		cmd[i].re = NULL;
		cmd[i].heredoc_id = -1;
		cmd[i].data = data;
		i++;
	}
}

void	data_init(t_data *data, char **env, char *cmd_buff)
{
	char	*temp;

	data->cmd_buff = cmd_buff;
	data->p_pid = getpid();
	data->last_exit_status = 0;
	temp = getcwd(data->path, 500);
	data->prev_dir = ft_strdup(temp);
	data->path_str = ft_strjoin(temp, "/");
	copy_env(data, env, 0);
}

int	is_q_closed(char *c, int i)
{
	while (c[i])
	{
		if (c[i] == '\'' || c[i] == '"')
		{
			i = find_next_q(c, c[i], i);
			if (!i)
				return (0);
		}
		i++;
	}
	return (1);
}

int	cmd_count(char *c, int i, int count, t_data *data)
{
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
			continue ;
		}
		i++;
	}
	data->cmd_n = count;
	return (count);
}
