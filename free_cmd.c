/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 19:12:09 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 21:13:05 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_p2(t_cmd *cmd, int i, int j)
{
	if (cmd[i].re)
	{
		j = 0;
		while (j < cmd[i].re_n)
		{
			if (cmd[i].re[j].f_name)
				free(cmd[i].re[j].f_name);
			if (ft_strlen(cmd[i].re[j].str))
				free(cmd[i].re[j].str);
			j++;
		}
		free(cmd[i].re);
	}
	if (cmd[i].op)
	{
		j = 0;
		while (j <= cmd[i].op_n)
		{
			free((cmd[i].op[j]));
			j++;
		}
		free(cmd[i].op);
	}
}

void	free_cmd(t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	while (i < cmd->data->cmd_n)
	{
		if (cmd[i].c_pre_parse)
			free(cmd[i].c_pre_parse);
		if (cmd[i].c)
			free(cmd[i].c);
		if (cmd[i].c_path)
			free(cmd[i].c_path);
		if (cmd[i].pipe_f_name)
			free(cmd[i].pipe_f_name);
		free_cmd_p2(cmd, i, j);
		i++;
	}
	free(cmd->data->cmd_buff);
}

void	free_data(t_data *data)
{
	int	j;

	j = 0;
	while (data->env[j])
		free(data->env[j++]);
	free(data->env[j]);
	free(data->env);
	free(data->prev_dir);
	free(data->path_str);
	free(data);
}

void	free_cmd_exit(t_cmd *cmd, int end)
{
	if (cmd)
	{
		free_cmd(cmd, 0);
		if (end)
			free_data(cmd->data);
		free(cmd);
	}
}

void	free_double_p(void **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p[i]);
	free(p);
}
