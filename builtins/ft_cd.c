/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:46:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/06 00:10:42 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void change_env_path(t_data *data, char *c, int j)
{
    char *temp;
    int k;

        while (c[j] != '\0')
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
                        return ;
                    }
                    k++;
                }
            }
            j++;
        }
}

void ft_cd(t_cmd *cmd)
{
	if (ft_strncmp(cmd->c, "cd", ft_strlen(cmd->c)+ 3))
		return ;
	cmd->data->prev_dir = getcwd(cmd->data->path, 500);
	change_env_path(cmd->data, ft_strjoin("OLDPWD=", cmd->data->prev_dir), 0);
	chdir(cmd->op[1]);
	cmd->data->path_str = getcwd(cmd->data->path, 500);
	change_env_path(cmd->data, ft_strjoin("PWD=", cmd->data->path_str), 0);
}
