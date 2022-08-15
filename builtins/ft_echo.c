/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:45:13 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/15 20:57:42 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd, int i)
{
	if (ft_strncmp(cmd->c, "echo", ft_strlen(cmd->c) + 5))
		return ;
	if (cmd->op_n == 2 && !ft_strncmp("-n", cmd->op[1], 4))
		return ;
	else if (cmd->op_n > 2 && !ft_strncmp("-n", cmd->op[1], 4))
		i = 2;
	while (i < cmd->op_n)
	{
		printf("%s", cmd->op[i]);
		i++;
		if (i < cmd->op_n)
			printf(" ");
	}
	if (cmd->op_n > 1)
		if (ft_strncmp("-n", cmd->op[1], 4))
			printf("\n");
	if (cmd->op_n == 1)
		printf("\n");
	cmd->data->last_exit_status = 0;
}
