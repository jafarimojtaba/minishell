/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:47:10 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/06 00:15:57 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_valid_export_arg(t_cmd *cmd, int i, int j)
{
    while (i < cmd->op_n)
    {
        j = 0;
        // printf("op= %s\n",cmd->op[i]);
        while (cmd->op[i][j] != '\0')
        {
            if(cmd->op[i][0] < 'A' || cmd->op[i][0] > 'z')
            {
                printf("export: %s: check naming rules\n", cmd->op[i]);
                return (0);
            }
            if (cmd->op[i][j] == ' ')
            {
                printf("export: %s: not a valid identifier\n", cmd->op[i]);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int is_pre_defined_env(char **env, t_cmd *cmd, int i, int j)
{
    char *temp;

    while (i < cmd->op_n)
    {
        while (cmd->op[i][j] != '\0')
        {
            if (cmd->op[i][j] == '=')
            {
                temp = ft_substr(cmd->op[i], 0, j);
                puts(temp);
                env[0] = temp;
            }
            j++;
        }
        i++;
    }
    return 0;
}
void ft_export(char **env, t_cmd *cmd)
{
    int i;
    
    i = 0;
    if (ft_strncmp(cmd->c, "export", ft_strlen(cmd->c)+ 7))
		return ;
    if (is_valid_export_arg(cmd, 1, 0) == 0)
    {
        cmd->data->last_exit_status = 1;
        return ;
    }
    if(is_pre_defined_env(env, cmd, 1, 0) == 0)
        return ;
    while (env[i])
    {
        // if(ft_strncmp(cmd.))
        i++;
    }
    
}