/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:45:10 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/11 12:07:50 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_cmd *cmd)
{
	int	i;

	if (ft_strncmp(cmd->c, "env", ft_strlen(cmd->c) + 4))
		return ;
	i = 0;
	while (cmd->data->env[i])
	{
		printf("%s\n", cmd->data->env[i]);
		i++;
	}
}
