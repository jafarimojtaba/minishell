/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:37:12 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/18 21:01:17 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// char *qq_dollar(char *cmd, int i)
// {
// 	int start;
// 	int end;
// 	char *first_str = NULL;
// 	char *dollar_str = NULL;
// 	char *second_str = NULL;
// 	char *tmp1;
// 	char *tmp2;
// 	char *tmp3;

// 	start = end = i + 1;
// 	while (cmd[i] != '"')
// 	{
// 		i++;
// 		if (cmd[i] == '$')
// 		{
// 			end = i - 1;
// 			first_str = ft_substr(cmd, start, end - start + 1);
// 			printf("first_str = %s\n", first_str);
// 			start = i + 1;
// 		}
// 		if (cmd[i] == ' ')
// 		{
// 			end = i - 1;
// 			dollar_str = ft_substr(cmd, start, end - start + 1);
// 			start = i;
// 			while (cmd[i] != ' ')
// 				i++;
// 		}
// 	}
// 	end = i - 1;
// 	second_str = ft_substr(cmd, start, end - start + 1);
// 	tmp1 = ft_strjoin(first_str, dollar_str);
// 	tmp2 = ft_strjoin(tmp1, second_str);
// 	tmp3 = ft_strjoin(tmp2, &cmd[end + 2]);
// 	return (tmp3);
// }

void ft_dollar_replace(t_cmd *cmd)
{
	int i;
	int end;
	int start = 0;
	int j;
	char *first_str = NULL;
	char *dollar_str = NULL;
	char *temp1;
	char *temp2;

	i = 0;
	while (i < cmd[0].cmd_n)
	{
		j = 0;
		while (cmd[i].c_pre_parse[j])
		{
			// printf("%c\n", cmd[i].c_pre_parse[j]);
			if (cmd[i].c_pre_parse[j] == '\'')
			{
				j++;
				while (cmd[i].c_pre_parse[j] != '\'' && cmd[i].c_pre_parse[j])
					j++;
				if (!cmd[i].c_pre_parse[j])
				{
					printf("not closing quotes\n");
					break;
				}
				// puts("Hi if");
			}
			else if (cmd[i].c_pre_parse[j] == '"')
			{
				j++;
				while (cmd[i].c_pre_parse[j] && cmd[i].c_pre_parse[j] != '"')
				{
					if (cmd[i].c_pre_parse[j] == '$')
					{
						first_str = ft_substr(cmd[i].c_pre_parse, 0, j);
						// printf("first_str=%s, j = %d#\n", first_str, j);
						start = j + 1;
						while (cmd[i].c_pre_parse[j] != '"' && cmd[i].c_pre_parse[j] != ' ' && cmd[i].c_pre_parse[j])
							j++;
						if (cmd[i].c_pre_parse[j] != '\0')
						{
							end = j - 1;
							dollar_str = getenv(ft_substr(cmd[i].c_pre_parse, start, end - start + 1));
							// printf("dollar_str=%s, j = %d#\n", dollar_str, j);
							temp1 = ft_strjoin(first_str, dollar_str);
							temp2 = ft_strjoin(temp1, &cmd[i].c_pre_parse[end + 1]);
							// printf("command = %s\n", cmd[i].c_pre_parse);
							cmd[i].c_pre_parse = temp2;
							// break;
						}
						else
							break;
					}
					j++;
				}
				// j = 0;
				// printf("command = %s\n", cmd[i].c_pre_parse);
				// continue;
				// j++;
			}
			j++;
		}
		i++;
	}
}