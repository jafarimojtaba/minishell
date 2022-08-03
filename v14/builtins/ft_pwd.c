/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:47:42 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/02 19:41:37 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pwd(t_cmd *cmd)
{
	char cwd[256];

	if (ft_strncmp(cmd->c, "pwd", ft_strlen(cmd->c)+ 4))
		return ;
	chdir();
}