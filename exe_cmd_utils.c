/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:46:43 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 12:56:28 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "cd", ft_strlen(str) + 3) || \
		!ft_strncmp(str, "echo", ft_strlen(str) + 5) || \
		!ft_strncmp(str, "pwd", ft_strlen(str) + 4) || \
		!ft_strncmp(str, "export", ft_strlen(str) + 7) || \
		!ft_strncmp(str, "unset", ft_strlen(str) + 6) || \
		!ft_strncmp(str, "env", ft_strlen(str) + 4) || \
		!ft_strncmp(str, "exit", ft_strlen(str) + 5))
		return (1);
	return (0);
}

int	is_sys_p2(char **env_var, char *str, t_cmd *cmd, int i)
{
	char	*tmp1;
	char	*tmp2;

	while (env_var[i])
	{
		tmp1 = ft_strjoin(env_var[i], "/");
		tmp2 = ft_strjoin(tmp1, str);
		free(tmp1);
		if (!access(tmp2, R_OK))
		{
			cmd->c_path = tmp2;
			free_double_p((void **)env_var);
			return (1);
		}
		else
			free(tmp2);
		i++;
	}
	return (0);
}

int	is_sys(t_cmd *cmd, int i)
{
	char	*str;
	char	**env_var;

	if (!access(cmd->c, R_OK))
	{
		cmd->c_path = ft_strdup(cmd->c);
		return (1);
	}
	str = cmd->c;
	env_var = ft_split(getenv("PATH"), ':');
	if (is_sys_p2(env_var, str, cmd, i))
		return (1);
	free_double_p((void **)env_var);
	return (0);
}
