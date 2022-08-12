/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:38:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 12:58:30 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_output_append(char *c, int j)
{
	if ((c[j] == '>' && c[j + 1] == '>' && !ft_strchr("<>", c[j + 2]) \
		&& j && !ft_strchr("<>", c[j - 1])) || (c[j] == '>' && c[j + 1] == '>' \
		&& !ft_strchr("<>", c[j + 2]) && !j))
		return (1);
	return (0);
}

int	is_in_or_out_re(char *c, int j)
{
	if (((c[j] == '<' || c[j] == '>') && !ft_strchr("<>", c[j + 1]) \
	&& j && !ft_strchr("<>", c[j - 1])) || ((c[j] == '<' || c[j] == '>') \
	&& !ft_strchr("<>", c[j + 1]) && !j))
		return (1);
	else
		return (0);
}

int	read_n_re(t_cmd *cmd, int j, int count)
{
	char	*c;

	c = cmd->c_pre_parse;
	while (c[j])
	{
		if (c[j] == '\'' || c[j] == '"')
		{
			j = find_next_q(c, c[j], j) + 1;
			continue ;
		}
		else if (is_output_append(c, j) || is_heredoc(c, j))
		{
			j += 2;
			count++;
			continue ;
		}
		else if (is_in_or_out_re(c, j))
			count++;
		j++;
	}
	return (count);
}

void	init_cmd_re_p2(t_cmd *cmd, int *id, int *j, int *start)
{
	if (is_output_append(cmd->c_pre_parse, *j))
	{
		*start = *j - 1;
		*j += 2;
		update_append_re_vars(cmd, id, j, *start);
	}
	else if (is_heredoc(cmd->c_pre_parse, *j))
	{
		*start = *j - 1;
		*j += 2;
		update_heredoc_re_vars(cmd, id, j, *start);
	}
	else if (is_in_or_out_re(cmd->c_pre_parse, *j))
	{
		*start = *j - 1;
		(*j)++;
		update_in_out_re_vars(cmd, id, j, *start);
	}
}

void	init_cmd_re(t_cmd *cmd, int i, int j, int id)
{
	int	start;

	while (i < cmd->re_n)
	{
		id = 0;
		while (cmd->c_pre_parse[j])
		{
			if (cmd->c_pre_parse[j] == '\'' || cmd->c_pre_parse[j] == '"')
				j = find_next_q(cmd->c_pre_parse, cmd->c_pre_parse[j], j);
			else
				init_cmd_re_p2(cmd, &id, &j, &start);
			j++;
		}
		i++;
	}
}
