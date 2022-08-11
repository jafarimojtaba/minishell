/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:47:10 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/11 12:08:38 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_export_arg(t_cmd *cmd, int i, int j)
{
	int	equal_sign;

	equal_sign = 0;
	while (cmd->op[i][j] != '\0')
	{
		if (cmd->op[i][0] < 'A' || cmd->op[i][0] > 'z')
		{
			printf("export: %s: check naming rules\n", cmd->op[i]);
			return (0);
		}
		if (cmd->op[i][j] == ' ')
		{
			printf("export: %s: not a valid identifier\n", cmd->op[i]);
			return (0);
		}
		if (cmd->op[i][j] == '=')
			equal_sign++;
		j++;
	}
	if (equal_sign != 1)
		return (0);
	return (1);
}

int	is_pre_defined_env_p2(t_cmd *cmd, int i, int j, char *temp)
{
	int	k;

	if (cmd->op[i][j] == '=')
	{
		temp = ft_substr(cmd->op[i], 0, j + 1);
		k = 0;
		while (cmd->data->env[k])
		{
			if (!ft_strncmp(temp, cmd->data->env[k], ft_strlen(temp)))
			{
				free(cmd->data->env[k]);
				cmd->data->env[k] = ft_strdup(cmd->op[i]);
				free(temp);
				return (1);
			}
			k++;
		}
	}
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	return (0);
}

int	is_pre_defined_env(t_cmd *cmd, int i, int j)
{
	char	*temp;

	temp = NULL;
	while (cmd->op[i][j] != '\0')
	{
		if (is_pre_defined_env_p2(cmd, i, j, temp))
			return (1);
		j++;
	}
	return (0);
}

void	add_to_env(t_cmd *cmd, int i, int j, int l)
{
	char	**temp;

	while (cmd->data->env[l])
		l++;
	temp = (char **)malloc((l + 2) * sizeof(char *));
	temp[l + 1] = NULL;
	while (cmd->data->env[j])
	{
		temp[j] = cmd->data->env[j];
		j++;
	}
	temp[j] = ft_strdup(cmd->op[i]);
	free(cmd->data->env);
	cmd->data->env = temp;
}

void	ft_export(t_cmd *cmd, int i)
{
	i = 1;
	if (ft_strncmp(cmd->c, "export", ft_strlen(cmd->c) + 7))
		return ;
	while (i < cmd->op_n)
	{
		if (is_valid_export_arg(cmd, i, 0))
		{
			if (is_pre_defined_env(cmd, i, 0) == 0)
				add_to_env(cmd, i, 0, 0);
		}
		i++;
	}
}
