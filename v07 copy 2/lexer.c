/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:06:47 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/17 18:05:21 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_count(char *cmd)
{
	int i;
	int end;
	int count;

	i = 0;
	end = 0;
	count = 1;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			end = i + 1;
			while (cmd[end] != cmd[i] && cmd[i])
			{
				if (!cmd[end])
				{
					printf("not closing quotes\n");
					break;
				}
				end++;
			}
			i = end;
		}
		else if (cmd[i] == '|')
		{
			i++;
			while (cmd[i] == ' ' || cmd[i] == '|')
				i++;
			if (cmd[i])
				count++;
		}
		i++;
	}
	return (count);
}

void ft_lexer(t_cmd *t_cmd, char *cmd)
{
    int i;
    int j;
	int end;
	int start;

	i = 0;
    j = 0;
	end = 0;
	start = 0;
	while (cmd[start] == ' ')
		start++;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			end = i + 1;
			while (cmd[end] != cmd[i] && cmd[i])
			{
				if (!cmd[end])
				{
					printf("not closing quotes\n");
					break;
				}
				end++;
			}
			i = end;
		}
		else if (cmd[i] == '|')
		{
            end = i - 1;
            if (cmd[i + 1] == ' ' || cmd[i + 1] == '|')
            {
                i++;
                while (cmd[i] == ' ' || cmd[i] == '|')
                    i++;
                i--;
            }
            while (cmd[end] == ' ')
                end--;
            t_cmd[j].c_pre_parse = ft_substr(cmd, start, end - start + 1);
			t_cmd[j].pipe_flag_after = 1;
			if (j > 0)
				t_cmd[j].pipe_flag_before = 1;
            j++;
            start = i + 1;
		}
		i++;
	}
    end = i;
    t_cmd[j].c_pre_parse = ft_substr(cmd, start, end - start);
	if (j > 0)
		t_cmd[j].pipe_flag_before = 1;
}