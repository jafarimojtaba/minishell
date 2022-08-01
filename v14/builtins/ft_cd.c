/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:46:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/01 22:08:47 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void ft_cd(t_cmd *cmd)
{
	char *write_cmd[] = { "/bin/sh", "-c", "cd ..", NULL };
	execve("/bin/sh", write_cmd, NULL);
	// chdir(cmd->c_pre_parse);
}