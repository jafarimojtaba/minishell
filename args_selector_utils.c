/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_selector_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:39:36 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 12:41:01 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	op_count_p2(char *c, int *j)
{
	while (c[*j] != ' ' && c[*j] != '\0')
	{
		if (c[*j] == '\'' || c[*j] == '"')
			*j = find_next_q(c, c[*j], *j);
		(*j)++;
	}
	while (c[*j] == ' ')
		(*j)++;
}

void	op_count(t_cmd *cmd, int j, int count)
{
	char	*c;

	c = NULL;
	c = cmd->c_pre_parse;
	while (c[j] != '\0')
	{
		while (c[j] == ' ')
			j++;
		if (c[j] == '\'' || c[j] == '"')
		{
			j = find_next_q(c, c[j], j);
			if (c[j + 1] != '\0' && c[j + 1] != ' ')
			{
				j++;
				while (c[j] != '\0' && c[j] != ' ')
					j++;
			}
			j++;
		}
		else
			op_count_p2(c, &j);
		count++;
	}
	cmd->op_n = count;
}

void	op_split_p2(char *c, int *j)
{
	*j = find_next_q(c, c[*j], *j);
	if (c[*j + 1] != '\0' && c[*j + 1] != ' ')
	{
		(*j)++;
		while (c[*j] != '\0' && c[*j] != ' ')
			(*j)++;
		if (c[*j] == ' ')
			(*j)--;
	}
}

void	op_split_p3(char *c, int *j)
{
	while (c[*j] != ' ' && c[*j] != '\0' && c[*j] != '|')
	{
		if (c[*j] == '\'' || c[*j] == '"')
			*j = find_next_q(c, c[*j], *j);
		(*j)++;
	}
}

void	op_split(t_cmd *cmd, int i, int j, int start)
{
	char	*c;

	c = cmd->c_pre_parse;
	cmd->op = (char **)malloc((cmd->op_n + 1) * sizeof(char *));
	cmd->op[cmd->op_n] = NULL;
	while (j < (int)ft_strlen(c) && i < (cmd->op_n))
	{
		while (c[j] == ' ')
		{
			j++;
			start++;
		}
		if (c[j] == '\'' || c[j] == '"')
		{
			op_split_p2(c, &j);
			start += 1;
		}
		else
			op_split_p3(c, &j);
		cmd->op[i] = ft_substr(c, start, j - start);
		i++;
		j++;
		start = j;
	}
}
