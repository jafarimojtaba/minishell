/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 11:18:25 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/05 22:17:50 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_next_q(char *c, int q, int i)
{
	i++;
	while (c[i] != q && c[i] != '\0')
		i++;
	if (c[i + 1] && ft_strchr("'\"", c[i + 1]))
	{
		q = c[i + 1];
		i += 2;
		while (c[i] != q && c[i])
			i++;
	}
	if (c[i] == q)
		return (i);
	else
		return (0);
}

int find_next_near_q(char *c, int q, int i)
{
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
	tmp1 = ft_substr(cmd, end + 1, ft_strlen(cmd) + 1);
	free(cmd);
	cmd = ft_strjoin(tmp, tmp1);
	free(tmp);
	free(tmp1);
	start = 0;
	while (cmd[start] == ' ')
		start++;
	tmp = ft_substr(cmd, start, ft_strlen(cmd) + 1);
	free(cmd);
	return (tmp);
}

void free_re(t_red *red, int i)
{
	while (i < red->red_n)
	{
		free(red->f_name);
		if (red->str)
			free(red->str);
		i++;
	}
	
}
