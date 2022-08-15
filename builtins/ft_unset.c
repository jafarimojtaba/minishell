/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:47:07 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/15 19:03:41 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_unset_arg(t_cmd *cmd, int i, int j)
{
	int	equal_sign;

	equal_sign = 0;
	while (j < (int)ft_strlen(cmd->op[i]))
	{
		if (cmd->op[i][0] < 'A' || cmd->op[i][0] > 'z')
		{
			printf("unset: %s: check naming rules\n", cmd->op[i]);
			return (0);
		}
		if (cmd->op[i][j] == ' ')
		{
			printf("unset: %s: not a valid identifier\n", cmd->op[i]);
			return (0);
		}
		if (cmd->op[i][j] == '=')
			equal_sign++;
		j++;
	}
	if (equal_sign > 0)
		return (0);
	return (1);
}

int	is_available_env(t_cmd *cmd, int i, int j)
{
	int	k;

	k = 0;
	while (cmd->data->env[k])
	{
		j = 0;
		while (cmd->data->env[k][j] != '=')
			j++;
		if ((int)ft_strlen(cmd->op[i]) != j)
		{
			k++;
			continue ;
		}
		if (!ft_strncmp(cmd->op[i], cmd->data->env[k], j))
		{
			return (k);
		}
		k++;
	}
	return (-1);
}

void	remove_from_env(t_data *data, int k, int l, int j)
{
	char	**temp;
	int		i;

	i = 0;
	while (data->env[l])
		l++;
	temp = (char **)malloc(l * sizeof(char *));
	while (data->env[j])
	{
		if (j != k)
		{
			temp[i] = data->env[j];
			i++;
		}
		else
			free(data->env[j]);
		j++;
	}
	temp[i] = NULL;
	free(data->env);
	data->env = temp;
}

void	ft_unset(t_cmd *cmd)
{
	int	i;
	int	k;

	i = 1;
	if (ft_strncmp(cmd->c, "unset", ft_strlen(cmd->c) + 6))
		return ;
	cmd->data->last_exit_status = 0;
	while (i < cmd->op_n)
	{
		if (is_valid_unset_arg(cmd, i, 0))
		{
			k = is_available_env(cmd, i, 0);
			if (k != -1)
				remove_from_env(cmd->data, k, 0, 0);
		}
		else
			cmd->data->last_exit_status = 1;
		i++;
	}
}
