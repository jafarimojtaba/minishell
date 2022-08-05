/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:47:14 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/05 09:53:01 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_exit(t_cmd *cmd)
{
	int i;

	i = 0;
	if (ft_strncmp(cmd->c, "exit", ft_strlen(cmd->c)+ 5))
		return ;
	if (cmd->op_n > 1)
		i = ft_atoi(cmd->op[1]);
	exit(i);
}