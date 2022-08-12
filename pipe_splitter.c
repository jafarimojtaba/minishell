/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:06:47 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 12:44:42 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_splitter_p2(t_cmd *cmd, int *i, int *start, int *end)
{
	if (cmd->data->cmd_buff[*i] == '\'' || cmd->data->cmd_buff[*i] == '"')
	{
		*end = find_next_q(cmd->data->cmd_buff, cmd->data->cmd_buff[*i], *i);
		*i = *end;
	}
	else if (cmd->data->cmd_buff[*i] == '|')
	{
		*end = *i - 1;
		if (cmd->data->cmd_buff[*i + 1] == ' ' || \
		cmd->data->cmd_buff[*i + 1] == '|')
		{
			while (cmd->data->cmd_buff[*i] == ' ' || \
			cmd->data->cmd_buff[*i] == '|')
				(*i)++;
			(*i)--;
		}
		while (cmd->data->cmd_buff[*end] == ' ')
			(*end)--;
		cmd->c_pre_parse = ft_substr(cmd->data->cmd_buff, \
		*start, *end - *start + 1);
		cmd->pipe_flag_after = 1;
		*start = *i + 1;
		return (1);
	}
	return (0);
}

void	pipe_splitter(t_cmd *cmd, char *c, int i, int j)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (c[start] == ' ')
		start++;
	while (c[i] != '\0')
	{
		if (j > 0)
			cmd[j].pipe_flag_before = 1;
		if (pipe_splitter_p2(&cmd[j], &i, &start, &end))
			j++;
		i++;
	}
	end = i;
	if (j < cmd->data->cmd_n)
	{
		cmd[j].c_pre_parse = ft_substr(c, start, end - start + 1);
		if (j > 0)
			cmd[j].pipe_flag_before = 1;
	}
}
