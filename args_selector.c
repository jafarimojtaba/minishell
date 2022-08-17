/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_selector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:23:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/17 16:05:58 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_start_and_end(char *c, int start, int end)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_substr(c, 0, start);
	temp2 = ft_substr(c, start + 1, end - start - 1);
	temp3 = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	temp1 = ft_substr(c, end + 1, ft_strlen(c));
	temp2 = ft_strjoin(temp3, temp1);
	free(temp1);
	free(temp3);
	return (temp2);
}

char	*op_q_re(char *c, int i, int start)
{
	char	*temp;

	while (i < (int)ft_strlen(c))
	{
		if (i < (int)ft_strlen(c) && ft_strchr("'\"", c[i]))
		{
			start = i;
			i = find_next_near_q(c, c[i], i);
			if (!i)
				break ;
			temp = c;
			c = remove_start_and_end(c, start, i);
			free(temp);
			i = 0;
		}
		i++;
	}
	return (c);
}

void	ft_args_selector(t_cmd *cmd, int n, int i, int j)
{
	char	*temp;

	while (i < n)
	{
		op_count(&cmd[i], 0, 0);
		op_split(&cmd[i], 0, 0, 0);
		if (cmd[i].c && ft_strncmp(cmd[i].c, "echo", 10))
		{
			j = 0;
			while (j < cmd[i].op_n)
			{
				temp = cmd[i].op[j];
				cmd[i].op[j] = op_q_re(cmd[i].op[j], 0, 0);
				j++;
			}
		}
		i++;
	}
}
