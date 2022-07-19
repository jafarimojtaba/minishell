/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:37:12 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/19 20:45:38 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo "hi | ||" | | you know you are a pie "|" | << hi | to you

char *ft_new_read(char *dlm)
{
	char *dl;
	char *bf;
	char *ret ="";
	dl = ft_strjoin(dlm, "hi");
	printf("%s#\n", dlm);
	while (ft_strncmp(dlm, dl, ft_strlen(dl) + 1) != 0)
	{
		bf = ret;
		dl = readline(">");
		if(ft_strncmp(dlm, dl, ft_strlen(dl) + 1) != 0)
		{
			ret = ft_strjoin(bf, dl);
			ret = ft_strjoin(ret, "\n");
		}
	}
	printf("ret=%s", ret);
	return (ret);
}

void ft_input_replace(t_cmd *cmd)
{
	int i;
	int end;
	int start = 0;
	int start1 = 0;
	int j;
	char *first_str = NULL;
	char *dollar_str = NULL;
	char *temp1;
	char *temp2;
	char *temp3;
	char *input_dlm;
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
				{
					j++;
					if (!cmd[i].c_pre_parse[j])
					{
						printf("not closing quotes dollar\n");
						break;
					}
				}

				// puts("Hi if");
			}
			else if (cmd[i].c_pre_parse[j] == '<' && cmd[i].c_pre_parse[j + 1] == '<' && cmd[i].c_pre_parse[j + 2] != '<')
			{
				first_str = ft_substr(cmd[i].c_pre_parse, 0, j);
				if (cmd[i].c_pre_parse[j - 1] != ' ')
					first_str = ft_strjoin(first_str, " ");
				// printf("first_str=%s, cmd_j =%s#\n", first_str, &cmd[i].c_pre_parse[j]);

				start1 = j - 1;
				j += 2;
				// while (cmd[i].c_pre_parse[j])
				// {
				while (cmd[i].c_pre_parse[j] == ' ')
					j++;
				// j++;
				start = j;
				if (cmd[i].c_pre_parse[j] == '\'' || cmd[i].c_pre_parse[j] == '"')
				{
					c = cmd[i].c_pre_parse[j];
					j++;
					while (cmd[i].c_pre_parse[j] != c && cmd[i].c_pre_parse[j])
						j++;
					if (!cmd[i].c_pre_parse[j])
						printf("not closing quotes\n");
					else
					{
						// printf("%s\n", &cmd[i].c_pre_parse[j]);
						input_dlm = ft_substr(cmd[i].c_pre_parse, start + 1, j - start - 1);
						temp1 = ft_new_read(input_dlm);
						temp1 = ft_strjoin(temp1, "\"");
						temp1 = ft_strjoin("\"", temp1);
						temp2 = ft_strjoin(first_str, temp1);
						temp3 = ft_strjoin(temp2, &cmd[i].c_pre_parse[j + 1]);

						cmd[i].c_pre_parse = temp3;
					}
				}
				else
				{
					while (cmd[i].c_pre_parse[j] != ' ' && cmd[i].c_pre_parse[j])
						j++;
					input_dlm = ft_substr(cmd[i].c_pre_parse, start, j - start + 1);
					temp1 = ft_new_read(input_dlm);
					temp1 = ft_strjoin(temp1, "\"");
					temp1 = ft_strjoin("\"", temp1);
					temp2 = ft_strjoin(first_str, temp1);
					temp3 = ft_strjoin(temp2, &cmd[i].c_pre_parse[j]);
					cmd[i].c_pre_parse = temp3;
				}
				// continue;
				// j++;
				// }
			}
			j++;
		}
		i++;
	}
}

void ft_dollar_no_q(t_cmd *cmd)
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
				while (cmd[i].c_pre_parse[j] != ' ' && cmd[i].c_pre_parse[j])
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
			}
			j++;
		}
		i++;
	}
}

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
								break;
							}
						}
						// j++;
						// if (cmd[i].c_pre_parse[j] == ' ' || cmd[i].c_pre_parse[j] == '"')
						// {
						// 	end = j - 1;
						// 	dollar_str = getenv(ft_substr(cmd[i].c_pre_parse, start, end - start + 1));
						// 	// printf("dollar_str=%s, j = %d#\n", dollar_str, j);
						// 	temp1 = ft_strjoin(first_str, dollar_str);
						// 	temp2 = ft_strjoin(temp1, &cmd[i].c_pre_parse[end + 1]);
						// 	// printf("command = %s\n", cmd[i].c_pre_parse);
						// 	cmd[i].c_pre_parse = temp2;
						// 	// break;
						// }
						// else
						// 	break;
					}
					j++;
				}
			}
			j++;
		}
		i++;
	}
}