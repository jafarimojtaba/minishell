/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:57:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/27 06:49:24 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", ft_strlen(str)) || !ft_strncmp(str, "cd", ft_strlen(str)) || !ft_strncmp(str, "pwd", ft_strlen(str)) || !ft_strncmp(str, "export", ft_strlen(str)) || !ft_strncmp(str, "unset", ft_strlen(str)) || !ft_strncmp(str, "env", ft_strlen(str)) || !ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	return (0);
}

int is_cmd(char *str)
{
	// return (1);
	if (is_builtin(str))
	{
		// printf("cmd is from builtins\n");
		// access("/bin/echo", R_OK);
		return (1);
	}
	// printf("cmd is not from builtins\n");
	return (0);
}

void cmd_c(t_cmd *cmd, int n)
{
	int i;
	int j;
	int start;
	int end;
	// char *op;
	char *str;

	i = 0;
	start = 0;
	while (i < n)
	{
		j = 0;
		start = 0;
		// printf("cmd_c_first=%s#\n",cmd[i].c_pre_parse);
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
				end = j - 1;
				str = ft_substr(cmd[i].c_pre_parse, start, j - start);
				// j++;
				
				cmd[i].c = str;
				// if (is_cmd(str))
				// {
				// 	cmd[i].c = str;
					break;
				// }
				// else
				// 	free(str);
				// j++;
			}
			else if (cmd[i].c_pre_parse[j] != '\'' && cmd[i].c_pre_parse[j] != '"')
			{
				while (cmd[i].c_pre_parse[j] != ' ' && cmd[i].c_pre_parse[j])
					j++;
				str = ft_substr(cmd[i].c_pre_parse, start, j);
				// if (is_cmd(str))
				// {
					cmd[i].c = str;
					break;
				// }
				// else
				// 	free(str);
				// cmd[i].c = str;
				
			}
			j++;
		}

		// else
		// {
		// 	while (cmd[i].c_pre_parse[j] != cmd[i].c_pre_parse[0])
		// 		j++;
		// 	cmd[i].c = ft_substr(cmd[i].c_pre_parse, start, j);
		// }
		while (cmd[i].c_pre_parse[j] == ' ')
			j++;
		cmd[i].end_of_c = j;
		// cmd[i].c = ft_strjoin(cmd[i].c, "\"");
		// cmd[i].c = ft_strjoin("\"", cmd[i].c);
		// printf("command c =%s#\n", cmd[i].c);
		cmd[i].c_pre_parse = &cmd[i].c_pre_parse[j];
		// op = ft_substr(cmd[i].c_pre_parse, j, ft_strlen(cmd[i].c_pre_parse) - j);
		// printf("option c =%s#\n", op);
		i++;
	}
}
