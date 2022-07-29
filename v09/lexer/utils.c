/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 11:18:25 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/26 12:05:12 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int find_next_q(char *c, int q, int i)
{
	// printf("str=%s, c=%c, i=%d]\n", c, q, i);
	i++;
	while (c[i] != q && c[i])
		i++;
	if (c[i] == q)
		return (i);
	else
		return (0);
}

char *remove_f_cmd_pre(char *cmd, int start, int end)
{
	char *tmp;
	char *tmp1;

	tmp = ft_substr(cmd, 0, start + 1);
	tmp1 = ft_substr(cmd, end + 1, ft_strlen(cmd));
	free(cmd);
	cmd = ft_strjoin(tmp, tmp1);
	free(tmp);
	free(tmp1);
	start = 0;
	while (cmd[start] == ' ')
		start++;
	tmp = ft_substr(cmd, start, ft_strlen(cmd));
	free(cmd);
	return (tmp);
}

void free_cmd(t_cmd *cmd, int i)
{
	while (i < cmd[0].cmd_n)
	{
		if(cmd[i].c)
			free(cmd[i].c);
		// if(cmd[i].c_buf)
		// 	free(cmd[i].c_buf);
		if(cmd[i].c_pre_parse)
			free(cmd[i].c_pre_parse);
		i++;
	}
}
