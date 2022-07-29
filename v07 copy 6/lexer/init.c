/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 11:16:20 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/24 11:39:19 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_q_closed(char *c, int i)
{
	while (c[i])
	{
		if (c[i] == '\'' || c[i] == '"')
		{
			i = find_next_q(c, c[i], i);
			if (!i)
				return(0);
		}
		i++;
	}
	return(1);
}

int	cmd_count(char *c, int i, int count)
{
	while (c[i])
	{
		if (c[i] == '\'' || c[i] == '"')
			i = find_next_q(c, c[i], i);
		else if (c[i] == '|')
		{
			i++;
			while (c[i] == ' ' || c[i] == '|')
				i++;
			if (c[i])
				count++;
		}
		i++;
	}
	return (count);
}
