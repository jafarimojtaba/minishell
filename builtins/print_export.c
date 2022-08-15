/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:06:56 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/15 20:53:35 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**creat_temp(t_cmd *cmd, int i)
{
	char **temp;
	while (cmd->data->env[i])
		i++;
	temp = (char **)malloc((i + 1) * sizeof(char *));
	temp[i] = NULL;
	i = 0;
	while (cmd->data->env[i])
	{
		temp[i] = ft_strdup(cmd->data->env[i]);
		i++;
	}
	return (temp);
}

void	check_smaller_str(char **temp, int i, int j, int k)
{
	char	*str;

	while (temp[k] && temp[i][j] != '\0' && temp[k][j] != '\0')
	{
		if (temp[i][j] == temp[k][j])
		{
			j++;
			continue;
		}
		if (temp[i][j] < temp[k][j])
		{
			str = temp[k];
			temp[k] = temp[i];
			temp[i] = str;
		}
		break;
		j++;
	}
}

void	print_temp(char **temp, int i)
{
	while (temp[i])
	{
		printf("declare -x %s\n", temp[i]);
		i++;
	}
}

int	print_export(t_cmd *cmd, int i, int k)
{
	char	**temp;

	temp = creat_temp(cmd, i);
	i = 0;
	while (temp[i])
	{
		k = 0;
		while (temp[k])
		{
			if (k == i)
			{
				k++;
				continue;
			}
			check_smaller_str(temp, i, 0, k);
			k++;
		}
		i++;
	}
	print_temp(temp, 0);
	free_double_p((void **)temp);
	return(1);
}
