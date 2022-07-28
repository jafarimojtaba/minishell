/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:06:47 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/28 09:56:41 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_splitter_p2(t_cmd *cmd, int *i, int *start, int *end)
{
	if (cmd->c_buf[*i] == '\'' || cmd->c_buf[*i] == '"')
	{
		*end = find_next_q(cmd->c_buf, cmd->c_buf[*i], *i);
		*i = *end;
	}
	else if (cmd->c_buf[*i] == '|')
	{
		*end = *i - 1;
		if (cmd->c_buf[*i + 1] == ' ' || cmd->c_buf[*i + 1] == '|')
		{
			while (cmd->c_buf[*i] == ' ' || cmd->c_buf[*i] == '|')
				(*i)++;
			(*i)--;
		}
		while (cmd->c_buf[*end] == ' ')
			(*end)--;
		cmd->c_pre_parse = ft_substr(cmd->c_buf, *start, *end - *start + 2);
		printf("prepars=%s#\n",cmd->c_pre_parse);
		cmd->pipe_flag_after = 1;
		*start = *i + 1;
		return (1);
	}
	return (0);
}
// echo hi how are you | grep cd" to lft" | "wc -c"
void	pipe_splitter(t_cmd *cmd, char *c, int i, int j)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (c[start] == ' ')
		start++;
	while (c[i])
	{
		if (j > 0)
			cmd[j].pipe_flag_before = 1;
		if (pipe_splitter_p2(&cmd[j], &i, &start, &end))
			j++;
		i++;
	}
	end = i;
	if (j < cmd[0].cmd_n)
	{
		cmd[j].c_pre_parse = ft_substr(c, start, end - start + 1);
		if (j > 0)
			cmd[j].pipe_flag_before = 1;
	}
}
