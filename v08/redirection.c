/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:57:21 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/24 11:40:13 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int read_n_re(t_cmd *cmd, int j, int count)
{
	char *c;

	c = cmd->c_pre_parse;
	while (c[j])
	{
		if (c[j] == '\'' || c[j] == '"')
		{
			j = find_next_q(c, c[j], j) + 1;
			continue;
		}
		else if ((c[j] == '>' && c[j + 1] == '>' && !ft_strchr("<>", c[j + 2]) && !ft_strchr("<>", c[j - 1]) && j) ||
				 (c[j] == '>' && c[j + 1] == '>' && !ft_strchr("<>", c[j + 2]) && !j))
		{
			j += 2;
			count++;
			continue;
		}
		else if (((c[j] == '<' || c[j] == '>') && !ft_strchr("<>", c[j + 1]) && !ft_strchr("<>", c[j - 1]) && j) ||
				 ((c[j] == '<' || c[j] == '>') && !ft_strchr("<>", c[j + 1]) && !j))
			count++;
		j++;
	}
	return (count);
}

char *find_file_name(char *c, int *j)
{
	int start;
	int end;

	while (c[*j] == ' ')
		(*j)++;
	// printf("ffn=%s\n", &c[*j]);
	// if (c[*j] == '\'' || c[*j] == '"')
	// {
	// 	// puts("hi");
	// 	start = *j + 1;
	// 	end = find_next_q(c, c[*j], *j);
	// 	// (*j)++;
	// 	return (ft_substr(c, start, end - start));
	// }
	// else
	// {
		start = *j;

		while (c[*j] != ' ' && c[*j] != '<' && c[*j] != '>' && c[*j] != '|' && c[*j])
			(*j)++;
		end = *j;
		// printf("end=%s\n", &c[*j]);
		return (ft_substr(c, start, end - start));
	// }
}
char *remove_f_cmd_pre(char *cmd, int start, int end)
{
	char *tmp;
	char *tmp1;

	tmp = ft_substr(cmd, 0, start + 1);
	// printf("tmp=%s#\n", tmp);
	tmp1 = ft_substr(cmd, end + 1, ft_strlen(cmd));
	// printf("tmp1=%s#\n", tmp1);
	cmd = ft_strjoin(tmp, tmp1);
	// printf("cmd=%s#\n", cmd);
	while (*cmd == ' ')
	{
		cmd++;
	}
	return(cmd);
}

//<f1 <f1 cat >f2 >f3
// cat <f1 <f1 >f2 >f3

void init_cmd_re(t_cmd *cmd, int i, int j)
{
	char *c;
	int id;
	int start;

	c = cmd->c_pre_parse;
	// printf("cmd1=%s\n", &c[j]);

	while (i < cmd->re_n)
	{
		id = 0;
		while (c[j])
		{
			// c = cmd->c_pre_parse;
			// printf("cw=%s\n", c);
			if (c[j] == '\'' || c[j] == '"')
			{
				// puts("if1");
				j = find_next_q(c, c[j], j);
				j++;
				continue;
			}
			else if ((c[j] == '>' && c[j + 1] == '>' && !ft_strchr("<>", c[j + 2]) && !ft_strchr("<>", c[j - 1]) && j) ||
					 (c[j] == '>' && c[j + 1] == '>' && !ft_strchr("<>", c[j + 2]) && !j))
			{
				// puts("if2");
				start = j - 1;
				j += 2;
				// printf("j+2 =%d\n", j);
				cmd->re[id].id = id;
				cmd->re[id].type = 1;
				cmd->re[id].is_apnd = 1;
				cmd->re[id].f_name = find_file_name(c, &j);
				// printf("j of end =%d\n", j);
				// printf("filename= %s",cmd->re[i].f_name);
				c = remove_f_cmd_pre(cmd->c_pre_parse, start, j - 1);
				cmd->c_pre_parse = c;
				id++;
				j = 0;
				continue;
			}
			else if (((c[j] == '<' || c[j] == '>') && !ft_strchr("<>", c[j + 1]) && !ft_strchr("<>", c[j - 1]) && j) ||
					 ((c[j] == '<' || c[j] == '>') && !ft_strchr("<>", c[j + 1]) && !j))
			{
				// puts("if3");
				start = j - 1;
				j++;
				// printf("j+1 =%s\n", &c[j]);
				cmd->re[id].id = id;
				cmd->re[id].type = 1;
				if (c[j - 1] == '<')
					cmd->re[id].type = 0;
				cmd->re[id].is_apnd = 0;
				cmd->re[id].f_name = find_file_name(c, &j);
				// printf("j of end =%s\n", &c[j]);
				// printf("filename= %s", cmd->re[i].f_name);
				c = remove_f_cmd_pre(cmd->c_pre_parse, start, j - 1);
				cmd->c_pre_parse = c;
				id++;
				j = 0;
				continue;
			}
			j++;
		}
		i++;
	}
}

void ft_redirection(t_cmd *cmd, int i)
{
	while (i < cmd->cmd_n)
	{
		cmd[i].re_n = read_n_re(&cmd[i], 0, 0);
		// printf("number of redirection=%d\n", cmd[i].re_n);
		cmd[i].re = (t_red *)malloc(cmd[i].re_n * sizeof(t_red));
		init_cmd_re(&cmd[i], 0, 0);
		for (size_t j = 0; j < cmd[i].re_n; j++)
		{
			printf("id = %d type = %d is_append = %d, file_name= %s\n",
				   cmd[i].re[j].id, cmd[i].re[j].type, cmd[i].re[j].is_apnd, cmd[i].re[j].f_name);
		}
		i++;
	}
}