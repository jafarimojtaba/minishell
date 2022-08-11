/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:23:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/11 10:30:02 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void op_count(t_cmd *cmd, int j, int count)
{
	char *c;

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
		{
			while (c[j] != ' ' && c[j] != '\0')
			{
				if (c[j] == '\'' || c[j] == '"')
				{
					j = find_next_q(c, c[j], j);
					// if (c[j + 1] != '\0' && c[j + 1] != ' ')
					// {
					// 	j++;
					// 	while (c[j] != '\0' && c[j] != ' ')
					// 		j++;
					// }
				}
				j++;
			}
			// j++;
			while (c[j] == ' ')
				j++;
		}
		count++;
		// j++;
	}
	cmd->op_n = count;
	// if(!ft_strncmp("exit", c, 4))
	// 	cmd->op_n = 2;
}

void op_split(t_cmd *cmd, int i, int j, int start)
{
	char *c;

	c = cmd->c_pre_parse;
	// printf("size =%zu\n", ft_strlen(c));
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
			j = find_next_q(c, c[j], j);
			if (c[j + 1] != '\0' && c[j + 1] != ' ')
			{
				j++;
				while (c[j] != '\0' && c[j] != ' ')
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
			while (c[j] != ' ' && c[j] != '\0' && c[j] != '|')
			{
				if (c[j] == '\'' || c[j] == '"')
				{
					j = find_next_q(c, c[j], j);
					// if (c[j + 1] != '\0' && c[j + 1] != ' ')
					// {
					// 	j++;
					// 	while (c[j] != '\0' && c[j] != ' ')
					// 		j++;
					// }
				}
				j++;
			}
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
	// printf("temp1 = %s\n", temp1);
	temp2 = ft_substr(c, start + 1, end - start - 1);
	// printf("temp2 = %s\n", temp2);
	temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	// printf("temp3 = %s\n", temp3);
	temp1 = ft_substr(c, end + 1, ft_strlen(c));
	// printf("temp1 = %s\n", temp1);
	temp2 = ft_strjoin(temp3, temp1);
	free(temp1);
	free(temp3);
	// printf("temp2 = %s\n", temp2);
	return (temp2);
}
// seperate cases for single quote and double qoute should be applied
char *op_q_re(char *c, int i, int start)
{
	char *temp;

	while (i < (int)ft_strlen(c))
	{
		if (i <  (int)ft_strlen(c) && ft_strchr("'\"", c[i]))
		{
			start = i;
			i = find_next_near_q(c, c[i], i);
			if (!i)
				break;
			temp = c;
			c = remove_start_and_end(c, start, i);
			free(temp);
			i = 0;
		}
		i++;
	}
	return (c);
}

void ft_args_selector(t_cmd *cmd, int n, int i, int j)
{
	char *temp;
	while (i < n)
	{
		// cmd[i].op = ft_split(cmd[i].c_pre_parse, ' ');
		op_count(&cmd[i], 0, 0);
		op_split(&cmd[i], 0, 0, 0);
		j = 0;
		while (j < cmd[i].op_n)
		{
			temp = cmd[i].op[j];
			cmd[i].op[j] = op_q_re(cmd[i].op[j], 0, 0);
			j++;
		}
		i++;
	}
}
