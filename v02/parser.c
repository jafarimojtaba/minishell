/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:23:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/17 09:18:48 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cmd_init(t_cmd *cmd, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		cmd[i].id = i;
		cmd[i].pipe_flag_before = 0;
		cmd[i].pipe_flag_after = 0;
		cmd[i].fd_in = 0;
		cmd[i].fd_out = 1;
		i++;
	}
}

void cmd_c(t_cmd *cmd, int n)
{
	int i;
	int j;
	int start;
	char *op;

	i = 0;
	start = 0;
	while (i < n)
	{
		j = 0;
		while (cmd[i].c_pre_parse[j] == ' ')
		{
			j++;
			start++;
		}
		if (cmd[i].c_pre_parse[0] != '\'' && cmd[i].c_pre_parse[0] != '"')
		{
			while (cmd[i].c_pre_parse[j] != ' ' && cmd[i].c_pre_parse[j])
				j++;
			cmd[i].c = ft_substr(cmd[i].c_pre_parse, start, j);
		}
		else
		{
			while (cmd[i].c_pre_parse[j] != cmd[i].c_pre_parse[0])
				j++;
			cmd[i].c = ft_substr(cmd[i].c_pre_parse, start, j);
		}
		while (cmd[i].c_pre_parse[j] == ' ')
			j++;
		cmd[i].end_of_c = j;
		printf("command c = %s\n", cmd[i].c);
		op = ft_substr(cmd[i].c_pre_parse, j, ft_strlen(cmd[i].c_pre_parse) - j);
		printf("option c = %s\n", op);
		i++;
	}
}

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
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			end = i + 1;
			while (cmd[end] != cmd[i] && cmd[end])
				end++;
			if(!cmd[end])
				printf("error! no closing quotes\n");
			i = end + 1;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>' && !ft_strchr("<|>", cmd[i + 2]) && !ft_strchr("<|>", cmd[i - 1]))
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
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			end = i + 1;
			while (cmd[end] != cmd[i] && cmd[end])
				end++;
			if(!cmd[end])
				printf("error! no closing quotes\n");
			i = end + 1;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>' && !ft_strchr("<|>", cmd[i + 2]) && !ft_strchr("<|>", cmd[i - 1]))
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
