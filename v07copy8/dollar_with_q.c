/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_with_q.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:59:33 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/28 10:28:31 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_str_env(t_cmd *cmd, int start, int *j, char *first_str)
{
	char	*temp1;
	char	*temp2;
	char	*dollar_str;

	(*j)++;
	dollar_str = ft_substr(cmd->c_pre_parse, start, *j - start + 1);
	// printf("dollarstr=%s#\n",dollar_str);
	temp1 = dollar_str;
	dollar_str = getenv(dollar_str);
	if (temp1)
		free(temp1);
	if (dollar_str)
	{
		temp1 = ft_strjoin(first_str, dollar_str);
		free(first_str);
		// if (dollar_str)
		// free(dollar_str);
		temp2 = ft_strjoin(temp1, &cmd->c_pre_parse[*j + 1]);
		free(temp1);
		free(cmd->c_pre_parse);
		cmd->c_pre_parse = temp2;
		return (1);
	}
	return (0);
}

void	no_dollar_var(t_cmd *cmd, int j, char *first_str)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(first_str, "");
	free(first_str);
	temp2 = ft_strjoin(temp1, &cmd->c_pre_parse[j]);
	free(temp1);
	free(cmd->c_pre_parse);
	cmd->c_pre_parse = temp2;
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

	while (cmd->c_pre_parse[*j] && cmd->c_pre_parse[*j] != '"')
	{
		if (cmd->c_pre_parse[*j] == '$')
		{
			first_str = ft_substr(cmd->c_pre_parse, 0, *j);
			(*j)++;
			start = *j;
			while (is_not_space_or_dollar(cmd, *j))
			{
				dollar_check = dollar_str_env(cmd, start, j, first_str);
				if (dollar_check)
					break ;
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
	while (i < cmd[0].cmd_n)
	{
		j = 0;
		while (cmd[i].c_pre_parse[j])
		{
			if (cmd[i].c_pre_parse[j] == '\'')
			{
				j = find_next_q(cmd[i].c_pre_parse, cmd[i].c_pre_parse[j], j);
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
