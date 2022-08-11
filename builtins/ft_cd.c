/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:46:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/10 23:06:15 by mjafari          ###   ########.fr       */
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
                    free(temp);
                    return;
                }
                k++;
            }
        }
        j++;
    }
    free(temp);
}

void ft_cd(t_cmd *cmd)
{
    char *temp;

    temp = NULL;

    if (ft_strncmp(cmd->c, "cd", ft_strlen(cmd->c) + 3))
        return;
    // if (cmd->data->prev_dir)
    free(cmd->data->prev_dir);
    temp = getcwd(cmd->data->path, 500);
    cmd->data->prev_dir = ft_strdup(temp);
    temp = ft_strjoin("OLDPWD=", cmd->data->prev_dir);
    change_env_path(cmd->data, temp, 0);
    free(temp);
    chdir(cmd->op[1]);
    free(cmd->data->path_str);
    temp = getcwd(cmd->data->path, 500);
    // cmd->data->path_str = ft_strdup(temp);
    cmd->data->path_str = ft_strjoin(temp, "/");
    temp = ft_strjoin("PWD=", cmd->data->path_str);
    change_env_path(cmd->data, temp, 0);
    free(temp);
}
