/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:57:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/27 23:19:40 by mjafari          ###   ########.fr       */
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

void cmd_c(t_cmd *cmd, int n, int i, int j)
{
	int start;
	// char *temp;

	while (i < n)
	{
		j = 0;
		start = 0;
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
				cmd[i].c = ft_substr(cmd[i].c_pre_parse, start, j - start);
					break ;
			}
			else if (cmd[i].c_pre_parse[j] != '\'' && cmd[i].c_pre_parse[j] != '"')
			{
				while (cmd[i].c_pre_parse[j] != ' ' && cmd[i].c_pre_parse[j])
					j++;
				cmd[i].c = ft_substr(cmd[i].c_pre_parse, start, j - start);
					break ;
			}
			j++;
		}
		while (cmd[i].c_pre_parse[j] == ' ')
			j++;
		// temp = cmd[i].c_pre_parse;
		// cmd[i].c_pre_parse = &cmd[i].c_pre_parse[j];
		// free(temp);
		i++;
	}
}
