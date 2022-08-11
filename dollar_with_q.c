/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_with_q.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:59:33 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/11 09:45:07 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(char *str, t_cmd *cmd)
{
	char *temp = NULL;
	int i = 0;
	int j = 0;
	while (cmd->data->env[i])
	{
		j = 0;
		while (cmd->data->env[i][j] != '\0' && cmd->data->env[i][j] != '=')
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
int dollar_str_env(t_cmd *cmd, int start, int *j, char *first_str)
{
	char *temp1;
	char *temp2;
	char *dollar_str;

	(*j)++;
	dollar_str = ft_substr(cmd->c_pre_parse, start, *j - start);
	// printf("dollarstr=%s#\n",dollar_str);
	if (!ft_strncmp(dollar_str, "?", ft_strlen(dollar_str)))
	{
		temp1 = dollar_str;
		dollar_str = ft_itoa(cmd->data->last_exit_status);
		free(temp1);
	}
	else
	{
		temp1 = dollar_str;
		dollar_str = ft_getenv(dollar_str, cmd);
		free(temp1);
	}
	if (dollar_str)
	{
		temp1 = ft_strjoin(first_str, dollar_str);
		// printf("temp1=%s#\n",temp1);
		free(first_str);
		if (dollar_str)
			free(dollar_str);
		temp2 = ft_strjoin(temp1, &cmd->c_pre_parse[*j]);
		// printf("temp2=%s#\n",temp2);
		free(temp1);
		free(cmd->c_pre_parse);
		cmd->c_pre_parse = temp2;
		return (1);
	}
	return (0);
}

void no_dollar_var(t_cmd *cmd, int j, char *first_str)
{
	char *temp1;
	char *temp2;

	temp1 = ft_strjoin(first_str, "");
	free(first_str);
	temp2 = ft_strjoin(temp1, &cmd->c_pre_parse[j]);
	free(temp1);
	free(cmd->c_pre_parse);
	cmd->c_pre_parse = temp2;
}

int is_not_space_or_dollar(t_cmd *cmd, int j)
{
	if (cmd->c_pre_parse[j] && !ft_strchr("$ '\"", cmd->c_pre_parse[j]))
		return (1);
	return (0);
}

void dollar_in_next_dq(t_cmd *cmd, int start, int *j, char *first_str)
{
	int dollar_check;

	while (cmd->c_pre_parse[*j] != '\0' && cmd->c_pre_parse[*j] != '"')
	{
		if (cmd->c_pre_parse[*j] == '$')
		{
			first_str = ft_substr(cmd->c_pre_parse, 0, *(j));
			// printf("first str:%s\n", first_str);
			(*j)++;
			start = *j;
			while (is_not_space_or_dollar(cmd, *j))
			{
				dollar_check = dollar_str_env(cmd, start, j, first_str);
				if (dollar_check)
				{
					*j = 0;
					return;
				}
			}
			if (!dollar_check)
				no_dollar_var(cmd, *j, first_str);
		}
		(*j)++;
	}
}

void dollar_with_q(t_cmd *cmd, int i, int j, int start)
{
	char *first_str;

	first_str = NULL;
	while (i < cmd->data->cmd_n)
	{
		j = 0;
		while (cmd[i].c_pre_parse[j] != '\0')
		{
			if (cmd[i].c_pre_parse[j] == '\'')
			{
				// puts("single quote");
				j = find_next_near_q(cmd[i].c_pre_parse, cmd[i].c_pre_parse[j], j);
				if (!j)
					break;
			}
			else if (cmd[i].c_pre_parse[j] == '"')
			{
				// puts(&cmd[i].c_pre_parse[j]);
				j++;
				dollar_in_next_dq(&cmd[i], start, &j, first_str);
				// j++;
			}
			j++;
		}
		i++;
	}
}
// echo "$USER" hi"$USER"       nhj
// 001234567891123456789212345678931