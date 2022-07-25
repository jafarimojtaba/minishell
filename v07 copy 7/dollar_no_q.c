/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_no_q.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:37:12 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/25 20:04:58 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo "hi | ||" | | you know you are a pie "|" | << hi | to you

void dollar_no_q(t_cmd *cmd)
{
	int i;
	int end;
	int start = 0;
	int j;
	char *first_str = NULL;
	char *dollar_str = NULL;
	char *temp1;
	char *temp2;
	char c;

	i = 0;
	while (i < cmd[0].cmd_n)
	{
		j = 0;
		while (cmd[i].c_pre_parse[j])
		{
			// printf("%c\n", cmd[i].c_pre_parse[j]);
			if (cmd[i].c_pre_parse[j] == '\'' || cmd[i].c_pre_parse[j] == '"')
			{
				c = cmd[i].c_pre_parse[j];
				j++;
				while (cmd[i].c_pre_parse[j] != c && cmd[i].c_pre_parse[j])
					j++;
				if (!cmd[i].c_pre_parse[j])
				{
					printf("not closing quotes\n");
					break;
				}
				// puts("Hi if");
			}
			else if (cmd[i].c_pre_parse[j] == '$')
			{
				j++;
				first_str = ft_substr(cmd[i].c_pre_parse, 0, j - 1);
				// printf("first_str=%s, j = %d#\n", first_str, j);
				start = j;
				while (cmd[i].c_pre_parse[j] != ' ' && cmd[i].c_pre_parse[j] && cmd[i].c_pre_parse[j] != '$')
				{
					j++;
					end = j;
					// printf("getenv= %s\n", ft_substr(cmd[i].c_pre_parse, start, end - start + 1));
					if (getenv(ft_substr(cmd[i].c_pre_parse, start, end - start + 1)))
					{
						dollar_str = getenv(ft_substr(cmd[i].c_pre_parse, start, end - start + 1));
						// printf("dollar_str=%s, j = %d#\n", dollar_str, j);
						temp1 = ft_strjoin(first_str, dollar_str);
						temp2 = ft_strjoin(temp1, &cmd[i].c_pre_parse[end + 1]);
						// printf("command = %s\n", cmd[i].c_pre_parse);
						cmd[i].c_pre_parse = temp2;
						// break;
					}
				}
				if (!dollar_str)
				{
					dollar_str = "";
					temp1 = ft_strjoin(first_str, dollar_str);
					temp2 = ft_strjoin(temp1, &cmd[i].c_pre_parse[end]);
					// printf("command = %s\n", cmd[i].c_pre_parse);
					cmd[i].c_pre_parse = temp2;
				}
			}
			j++;
		}
		i++;
	}
}

