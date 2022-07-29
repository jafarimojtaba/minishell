/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:57:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/28 11:45:27 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cmd_c(t_cmd *cmd, int n, int i, int j)
{
	int start;

	while (i < n)
	{
		j = 0;
		start = 0;
		while (cmd[i].c_pre_parse[j] == ' ')
		{
			j++;
			start++;
		}
		while (cmd[i].c_pre_parse[j])
		{
			if (cmd[i].c_pre_parse[j] == '\'' || cmd[i].c_pre_parse[j] == '"')
			{
				start = j + 1;
				j = find_next_q(cmd[i].c_pre_parse, cmd[i].c_pre_parse[j], j);
				cmd[i].c = ft_substr(cmd[i].c_pre_parse, start, j - start);
					break ;
			}
			else if (cmd[i].c_pre_parse[j] != '\'' && cmd[i].c_pre_parse[j] != '"')
			{
				while (cmd[i].c_pre_parse[j] != ' ' && cmd[i].c_pre_parse[j])
					j++;
				cmd[i].c = ft_substr(cmd[i].c_pre_parse, start, j - start);
					break ;
			}
			j++;
		}
		while (cmd[i].c_pre_parse[j] == ' ')
			j++;
		i++;
	}
}
