/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_no_q.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:37:12 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 13:07:54 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_dollar(t_cmd *cmd, int start, int *j, char *first_str)
{
	int	dollar_check;

	dollar_check = 0;
	first_str = ft_substr(cmd->c_pre_parse, 0, *j);
	(*j)++;
	start = *j;
	while (*j < (int)ft_strlen(cmd->c_pre_parse) \
	&& !ft_strchr("$ <>'\"", cmd->c_pre_parse[*j]))
	{
		dollar_check = dollar_str_env(cmd, start, j, first_str);
		if (dollar_check)
			break ;
	}
	if (!dollar_check)
		no_dollar_var(cmd, *j, first_str);
}

void	dollar_no_q(t_cmd *cmd, int i, int j, int start)
{
	char	*first_str;

	first_str = NULL;
	while (i < cmd->data->cmd_n)
	{
		j = 0;
		while (j < (int)ft_strlen(cmd[i].c_pre_parse))
		{
			if (cmd[i].c_pre_parse[j] == '\'' || cmd[i].c_pre_parse[j] == '"')
			{
				j = find_next_near_q(cmd[i].c_pre_parse, \
					cmd[i].c_pre_parse[j], j);
				if (!j)
					break ;
			}
			else if (cmd[i].c_pre_parse[j] == '$')
			{
				end_of_dollar(&cmd[i], start, &j, first_str);
				j = 0;
				continue ;
			}
			j++;
		}
		i++;
	}
}
