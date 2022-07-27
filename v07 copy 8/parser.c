/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:23:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/26 18:17:41 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cmd_init(t_cmd *cmd, char *cmd_buff, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		cmd[i].id = i;
		cmd[i].heredoc_id = -1;
		cmd[i].pipe_flag_before = -1;
		cmd[i].pipe_flag_after = -1;
		cmd[i].fd_in = 0;
		cmd[i].fd_out = 1;
		cmd[i].cmd_n = n;
		cmd[i].c_buf = cmd_buff;
		i++;
	}
	// printf("n == %d\n", n);
}



void args_selector(t_cmd *cmd, int n)
{
	int i = 0;
	int j = 0;
	int start = 0;
	char *c;
	int count =0;

	while (i < n)
	{
		j = 0;
		c = cmd[i].c_pre_parse;
		while (c[j])
		{
			if (c[j] == '\'' || c[j] == '"')
			{
				start = j;
				j = find_next_q(c, c[j], j);
			}
			while (c[j] != ' ' && c[j])
				j++;
			count++;
			while (c[j] == ' ')
				j++;
			j++;
		}
		cmd[i].op = (char **)malloc(count * sizeof(char *));
		j = 0;
		count = 0;
		while (c[j])
		{
			start = j;
			if (c[j] == '\'' || c[j] == '"')
			{
				start = j;
				j = find_next_q(c, c[j], j);
				cmd[i].op[count++] = ft_substr(c, start, j - start + 1);
			}
			while (c[j] != ' ' && c[j])
				j++;
			if (c[j] != '\'' || c[j] != '"')
				cmd[i].op[count++] = ft_substr(c, start, j - start + 1);
			printf("op %d=%s#\n",count, cmd[i].op[count]);
			// if (c[j] == ' ')
			// 	j++;
			j++;
		}
		i++;
	}
}
// int cmd_num(char *cmd)
// {
// 	int count = 1;
// 	int i = 0;
// 	int start = 0;
// 	int end = 0;

// 	while (cmd[i])
// 	{
// 		while (cmd[i] == ' ')
// 			i++;
// 		if (cmd[i] == '\'' || cmd[i] == '"')
// 		{
// 			end = i + 1;
// 			while (cmd[end] != cmd[i] && cmd[end])
// 				end++;
// 			if(!cmd[end])
// 				printf("error! no closing quotes\n");
// 			i = end + 1;
// 		}
// 		else if (cmd[i] == '>' && cmd[i + 1] == '>' && !ft_strchr("<|>", cmd[i + 2]) && !ft_strchr("<|>", cmd[i - 1]))
// 		{
// 			count++;
// 		}
// 		else if (cmd[i] == '<' && cmd[i + 1] == '<' && !ft_strchr("<|>", cmd[i + 2]) && !ft_strchr("<|>", cmd[i - 1]))
// 		{
// 			count++;
// 		}
// 		else if (ft_strchr("<|>", cmd[i]) && !ft_strchr("<|>", cmd[i + 1]) && !ft_strchr("<|>", cmd[i - 1]))
// 		{
// 			count++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

// void cmd_fill(t_cmd *cmd_s, char *cmd)
// {
// 	int c = 0;
// 	int i = 0;
// 	int start = 0;
// 	int end = 0;

// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\'' || cmd[i] == '"')
// 		{
// 			end = i + 1;
// 			while (cmd[end] != cmd[i] && cmd[end])
// 				end++;
// 			if(!cmd[end])
// 				printf("error! no closing quotes\n");
// 			i = end + 1;
// 		}
// 		else if (cmd[i] == '>' && cmd[i + 1] == '>' && !ft_strchr("<|>", cmd[i + 2]) && !ft_strchr("<|>", cmd[i - 1]))
// 		{
// 			i += 2;
// 			end = i;
// 			cmd_s[c].c_pre_parse = ft_substr(cmd, start, end - start);
// 			printf("command = %s\n", cmd_s[c].c_pre_parse);
// 			start = end;
// 			c++;
// 		}
// 		else if (cmd[i] == '<' && cmd[i + 1] == '<' && !ft_strchr("<|>", cmd[i + 2]) && !ft_strchr("<|>", cmd[i - 1]))
// 		{
// 			i += 2;
// 			end = i;
// 			cmd_s[c].c_pre_parse = ft_substr(cmd, start, end - start);
// 			printf("command = %s\n", cmd_s[c].c_pre_parse);

// 			start = end;
// 			c++;
// 		}
// 		else if (ft_strchr("<|>", cmd[i]) && !ft_strchr("<|>", cmd[i + 1]) && !ft_strchr("<|>", cmd[i - 1]))
// 		{
// 			i++;
// 			end = i;
// 			cmd_s[c].c_pre_parse = ft_substr(cmd, start, end - start);
// 			printf("command = %s\n", cmd_s[c].c_pre_parse);
// 			start = end;
// 			c++;
// 		}
// 		i++;
// 	}
// 	end = i;
// 	cmd_s[c].c_pre_parse = ft_substr(cmd, start, end - start);
// 	printf("command = %s\n", cmd_s[c].c_pre_parse);
// }

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
