/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:23:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/14 22:18:25 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_num(char *cmd)
{
	int count = 1;
	int i = 0;
	int start = 0;
	int end = 0;

	while (cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		if (cmd[i] == '>' && cmd[i + 1] == '>' && !ft_strchr("<|>", cmd[i + 2]) && !ft_strchr("<|>", cmd[i - 1]))
		{
			count++;
		}
		else if (cmd[i] == '<' && cmd[i + 1] == '<' && !ft_strchr("<|>", cmd[i + 2]) && !ft_strchr("<|>", cmd[i - 1]))
		{
			count++;
		}
		else if (ft_strchr("<|>", cmd[i]) && !ft_strchr("<|>", cmd[i + 1]) && !ft_strchr("<|>", cmd[i - 1]))
		{
			count++;
		}
		i++;
	}
	return (count);
}

void cmd_fill(t_cmd *cmd_s, char *cmd)
{
	int c = 0;
	int i = 0;
	int start = 0;
	int end = 0;

	while (cmd[i])
	{
		if (cmd[i] == '>' && cmd[i + 1] == '>' && !ft_strchr("<|>", cmd[i + 2]) && !ft_strchr("<|>", cmd[i - 1]))
		{
			i += 2;
			end = i;
			cmd_s[c].c_pre_parse = ft_substr(cmd, start, end - start);
			printf("command = %s\n", cmd_s[c].c_pre_parse);

			start = end;
			c++;
		}
		else if (cmd[i] == '<' && cmd[i + 1] == '<' && !ft_strchr("<|>", cmd[i + 2]) && !ft_strchr("<|>", cmd[i - 1]))
		{
			i += 2;
			end = i;
			cmd_s[c].c_pre_parse = ft_substr(cmd, start, end - start);
			printf("command = %s\n", cmd_s[c].c_pre_parse);

			start = end;
			c++;
		}
		else if (ft_strchr("<|>", cmd[i]) && !ft_strchr("<|>", cmd[i + 1]) && !ft_strchr("<|>", cmd[i - 1]))
		{
			i++;
			end = i;
			cmd_s[c].c_pre_parse = ft_substr(cmd, start, end - start);
			printf("command = %s\n", cmd_s[c].c_pre_parse);

			start = end;
			c++;
		}
		i++;
	}
	end = i;
	cmd_s[c].c_pre_parse = ft_substr(cmd, start, end - start);
	printf("command = %s\n", cmd_s[c].c_pre_parse);
}

// char **split_command(char *cb)
// {
// 	char *c;
// 	// int start = 0;
// 	int end = 0;
// 	int i = 0;
// 	while(valid_char(cb[i]))
// 	{
// 		i

// 	}
// }