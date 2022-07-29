/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 18:48:00 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/25 17:34:06 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*first_str_space(char *first_str)
{
	char	*temp;

	temp = first_str;
	first_str = ft_strjoin(first_str, " ");
	free(temp);
	return (first_str);
}

int	heredoc_str_q(t_cmd *cmd, char *first_str, int start, int j)
{
	j = find_next_q(cmd->c_pre_parse, cmd->c_pre_parse[j], j);
	heredoc_str(cmd, first_str, start, j);
	return (j);
}

int	heredoc_str_space(t_cmd *cmd, char *first_str, int start, int *j)
{
	if (cmd->c_pre_parse[*j] == '\'' || cmd->c_pre_parse[*j] == '"')
	{
		*j = heredoc_str_q(cmd, first_str, start, *j);
		return (0);
	}
	else
	{
		while (cmd->c_pre_parse[*j] != ' ' && cmd->c_pre_parse[*j])
			(*j)++;
		*j = heredoc_str(cmd, first_str, start, *j);
		return (1);
	}	
}

void	heredoc_input(t_cmd *cmd, int i, int j, int start)
{
	char	*first_str;

	while (i < cmd[0].cmd_n)
	{
		j = 0;
		while (cmd[i].c_pre_parse[j])
		{
			if (cmd[i].c_pre_parse[j] == '\'' || cmd[i].c_pre_parse[j] == '"')
				j = find_next_q(cmd[i].c_pre_parse, cmd[i].c_pre_parse[j], j);
			else if (is_heredoc(cmd[i].c_pre_parse, j))
			{
				first_str = ft_substr(cmd[i].c_pre_parse, 0, j);
				if (cmd[i].c_pre_parse[j - 1] != ' ')
					first_str = first_str_space(first_str);
				j += 2;
				while (cmd[i].c_pre_parse[j] == ' ')
					j++;
				start = j;
				if (heredoc_str_space(&cmd[i], first_str, start, &j))
					continue ;
			}
			j++;
		}
		i++;
	}
}
