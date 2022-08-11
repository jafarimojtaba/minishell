/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:57:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/09 19:03:51 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_c_2(t_cmd *cmd, int *j, int *start)
{
	while (cmd->c_pre_parse[*j])
	{
		if (cmd->c_pre_parse[*j] == '\'' || cmd->c_pre_parse[*j] == '"')
		{
			*start = *j + 1;
			*j = find_next_q(cmd->c_pre_parse, cmd->c_pre_parse[*j], *j);
			cmd->c = ft_substr(cmd->c_pre_parse, *start, *j - *start);
			break ;
		}
		else if (cmd->c_pre_parse[*j] != '\'' \
			&& cmd->c_pre_parse[*j] != '"')
		{
			while (cmd->c_pre_parse[*j] != ' ' && cmd->c_pre_parse[*j])
				(*j)++;
			cmd->c = ft_substr(cmd->c_pre_parse, *start, *j - *start);
			break ;
		}
		(*j)++;
	}
}

void	cmd_c(t_cmd *cmd, int n, int i, int j)
{
	int	start;

	while (i < n)
	{
		j = 0;
		start = 0;
		while (cmd[i].c_pre_parse[j] == ' ')
		{
			j++;
			start++;
		}
		cmd_c_2(&cmd[i], &j, &start);
		while (cmd[i].c_pre_parse[j] == ' ')
			j++;
		i++;
	}
}
