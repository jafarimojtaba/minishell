/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:46:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/15 19:00:22 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_path(t_data *data, char *c, int j)
{
	char	*temp;
	int		k;

	while (j < (int)ft_strlen(c))
	{
		if (c[j] == '=')
		{
			temp = ft_substr(c, 0, j + 1);
			k = 0;
			while (data->env[k])
			{
				if (!ft_strncmp(temp, data->env[k], ft_strlen(temp)))
				{
					free(data->env[k]);
					data->env[k] = ft_strdup(c);
					free(temp);
					return ;
				}
				k++;
			}
		}
		j++;
	}
	free(temp);
}

int	cd_error_check(t_cmd *cmd)
{
	if (ft_strncmp(cmd->c, "cd", ft_strlen(cmd->c) + 3))
		return (1);
	if (cmd->op_n > 2)
	{
		printf("cd: too many arguments\n");
		cmd->data->last_exit_status = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_cmd *cmd)
{
	char	*temp;

	temp = NULL;
	if (cd_error_check(cmd))
		return ;
	free(cmd->data->prev_dir);
	temp = getcwd(cmd->data->path, 500);
	cmd->data->prev_dir = ft_strdup(temp);
	temp = ft_strjoin("OLDPWD=", cmd->data->prev_dir);
	change_env_path(cmd->data, temp, 0);
	free(temp);
	if (cmd->op_n == 1)
	{
		temp = ft_getenv("HOME", cmd);
		chdir(temp);
		free(temp);
	}
	else
		chdir(cmd->op[1]);
	free(cmd->data->path_str);
	temp = getcwd(cmd->data->path, 500);
	cmd->data->path_str = ft_strjoin(temp, "/");
	temp = ft_strjoin("PWD=", cmd->data->path_str);
	change_env_path(cmd->data, temp, 0);
	free(temp);
	cmd->data->last_exit_status = 0;
}
