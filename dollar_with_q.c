/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_with_q.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:59:33 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 13:23:11 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str, t_cmd *cmd)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	temp = NULL;
	while (cmd->data->env[i])
	{
		j = 0;
		while (j < (int)ft_strlen(cmd->data->env[i]) && \
		cmd->data->env[i][j] != '=')
			j++;
		temp = ft_substr(cmd->data->env[i], 0, j);
		if (!ft_strncmp(str, temp, ft_strlen(temp) + ft_strlen(str)))
		{
			free(temp);
			temp = ft_strdup(&cmd->data->env[i][j + 1]);
			return (temp);
		}
		free(temp);
		i++;
	}
	return (NULL);
}

int	is_not_space_or_dollar(t_cmd *cmd, int j)
{
	if (cmd->c_pre_parse[j] && !ft_strchr("$ '\"", cmd->c_pre_parse[j]))
		return (1);
	return (0);
}

void	dollar_in_next_dq(t_cmd *cmd, int start, int *j, char *first_str)
{
	int	dollar_check;

	while (*j < (int)ft_strlen(cmd->c_pre_parse) && cmd->c_pre_parse[*j] != '"')
	{
		if (cmd->c_pre_parse[*j] == '$')
		{
			first_str = ft_substr(cmd->c_pre_parse, 0, *(j));
			(*j)++;
			start = *j;
			while (is_not_space_or_dollar(cmd, *j))
			{
				dollar_check = dollar_str_env(cmd, start, j, first_str);
				if (dollar_check)
				{
					*j = 0;
					return ;
				}
			}
			if (!dollar_check)
				no_dollar_var(cmd, *j, first_str);
		}
		(*j)++;
	}
}

void	dollar_with_q(t_cmd *cmd, int i, int j, int start)
{
	char	*first_str;

	first_str = NULL;
	while (i < cmd->data->cmd_n)
	{
		j = 0;
		while (j < (int)ft_strlen(cmd[i].c_pre_parse))
		{
			if (cmd[i].c_pre_parse[j] == '\'')
			{
				j = find_next_near_q(cmd[i].c_pre_parse, \
				cmd[i].c_pre_parse[j], j);
				if (!j)
					break ;
			}
			else if (cmd[i].c_pre_parse[j] == '"')
			{
				j++;
				dollar_in_next_dq(&cmd[i], start, &j, first_str);
			}
			j++;
		}
		i++;
	}
}
