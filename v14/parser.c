/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:23:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/01 21:11:03 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  op_count(t_cmd *cmd, int j, int count)
{
	char *c;

	c= NULL;
	c = cmd->c_pre_parse;
	while (c[j])
	{
		while (c[j] == ' ')
			j++;
		if (c[j] == '\'' || c[j] == '"')
		{
			j = find_next_q(c, c[j], j);
			if (c[j + 1] && c[j + 1] != ' ')
			{
				j++;
				while (c[j] && c[j] != ' ')
					j++;
			}
		}
		else
		{
			while (c[j] != ' ' && c[j])
				j++;
			while (c[j] == ' ')
			j++;
		}
		count++;
		j++;
	}
	cmd->op_n = count;
	if(!ft_strncmp("exit", c, 4))
		cmd->op_n = 2;
}

void op_split(t_cmd *cmd, int i, int j, int start)
{
	char *c;

	c = cmd->c_pre_parse;
	// printf("size =%zu\n", ft_strlen(c));
	cmd->op = (char **)calloc((cmd->op_n) + 1 , sizeof(char *));
	while (c[j] && i < (cmd->op_n))
	{
		while (c[j] == ' ')
		{
			j++;
			start++;
		}
		if (c[j] == '\'' || c[j] == '"')
		{
			j = find_next_q(c, c[j], j);
			if(c[j +1] && c[j + 1] != ' ')
			{
				j++;
				while (c[j] && c[j] != ' ')
					j++;
				if (c[j] == ' ')
					j--;
			}
			cmd->op[i] = ft_substr(c, start, j - start + 1);
			// printf("op %d form %d =%s#\n", i, cmd->op_n, cmd->op[i]);
			i++;
		}
		else
		{
			while (c[j] != ' ' && c[j] && c[j] != '|')
				j++;
			cmd->op[i] = ft_substr(c, start, j - start);
			// printf("op %d form %d =%s#\n", i, cmd->op_n, cmd->op[i]);
			i++;
		}
		j++;
		start = j;
	}
}

char *remove_start_and_end(char *c, int start, int end)
{
	char *temp1;
	char *temp2;
	char *temp3;

	temp1 = ft_substr(c, 0, start);
	temp2 = ft_substr(c, start + 1 , end - start - 1);
	temp3 = ft_strjoin(temp1, temp2);
	temp1 = ft_substr(c, end + 1, ft_strlen(c));
	temp2 = ft_strjoin(temp3, temp1);
	return(temp2);
}

char *op_space_re(char *c, int i, int start)
{
	while (c[i])
	{
		if (ft_strchr("'\"", c[i]))
		{
			start = i;
			i = find_next_near_q(c, c[i], i);
			c = remove_start_and_end(c, start, i);
			i = 0;
		}
		i++;
	}
	return(c);
}

void ft_args_selector(t_cmd *cmd, int n, int i, int j)
{
	while (i < n)
	{
		// cmd[i].op = ft_split(cmd[i].c_pre_parse, ' ');
		op_count(&cmd[i], 0, 0);
		op_split(&cmd[i], 0, 0, 0);
		j = 0;
		while(j < cmd[i].op_n)
		{
			cmd[i].op[j] = op_space_re(cmd[i].op[j], 0, 0);
			j++;
		}
		i++;
	}
}
