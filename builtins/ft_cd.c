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

void ft_cd(t_cmd *cmd)
{
	if (ft_strncmp(cmd->c, "cd", ft_strlen(cmd->c)+ 3))
		return ;
	cmd->data->prev_dir = getcwd(cmd->data->path, 500);
	chdir(cmd->op[1]);
	cmd->data->path_str = getcwd(cmd->data->path, 500);
}
