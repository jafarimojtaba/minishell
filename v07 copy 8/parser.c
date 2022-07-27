/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:23:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/27 19:58:46 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cmd_init(t_cmd *cmd, char *cmd_buff, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		cmd[i].id = i;
		cmd[i].heredoc_id = -1;
		cmd[i].pipe_flag_before = -1;
		cmd[i].pipe_flag_after = -1;
		cmd[i].fd_in = 0;
		cmd[i].fd_out = 1;
		cmd[i].cmd_n = n;
		cmd[i].c_buf = cmd_buff;
		cmd[i].op_n = 0;
		cmd[i].re_n = 0;
		i++;
	}
}

void op_count(t_cmd *cmd, int start, int j, int count)
{
	char *c;

	c = cmd->c_pre_parse;
	while (c[j])
	{
		while (c[j] == ' ')
			j++;
		if (c[j] == '\'' || c[j] == '"')
		{
			start = j;
			j = find_next_q(c, c[j], j);
		}
		while (c[j] != ' ' && c[j])
			j++;
		count++;
		j++;
	}
	cmd->op_n = count;
}

void op_split(t_cmd *cmd, int i, int j, int start)
{
	char *c;

	c = cmd->c_pre_parse;
	cmd->op = (char **)malloc(cmd->op_n * sizeof(char *));
	while (c[j] && i < cmd->op_n)
	{
		while (c[j] == ' ' && c[j])
			j++;
		start = j;
		if (c[j] == '\'' || c[j] == '"')
		{
			j = find_next_q(c, c[j], j);
			cmd->op[i++] = ft_substr(c, start + 1, j - start - 1);
		}
		else
		{
			while (c[j] != ' ' && c[j])
				j++;
			cmd->op[i++] = ft_substr(c, start, j - start);
		}
		j++;
	}
}

void args_selector(t_cmd *cmd, int n, int i)
{
	while (i < n)
	{
		op_count(&cmd[i], 0, 0, 0);
		op_split(&cmd[i], 0, 0, 0);
		i++;
	}
}
