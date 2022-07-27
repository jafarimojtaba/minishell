/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 11:16:20 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/24 17:42:33 by mjafari          ###   ########.fr       */
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
	printf("size = %zu, c in counter=%s\n", ft_strlen(c), &c[i]);
	while (c[i])
	{
		if (c[i] == '\'' || c[i] == '"')
			i = find_next_q(c, c[i], i);
		else if (c[i] == '|' && c[i + 1])
		{
			i++;
			while (c[i] == ' ')
				i++;
			if (c[i])
				count++;
			continue;
		}
		i++;
	}
	return (count);
}
