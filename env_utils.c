/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 23:44:09 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/06 00:07:05 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void copy_env(t_data *data, char **env, int i)
{
    char **env_dup;
    char buf[500];

    while (env[i])
        i++;
    env_dup = (char **)malloc((i + 1) * sizeof(char *));
    i = 0;
    while (env[i])
    {
        env_dup[i] = ft_strdup(env[i]);
        // puts(env_dup[i]);
        i++;
    }
    env_dup[i] = ft_strjoin("OLDPWD=", getcwd(buf, 500));
    // puts(env_dup[i]);
    data->env = env_dup;
}