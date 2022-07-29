/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:42:56 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/28 20:31:29 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *str)
{
	if (!ft_strncmp(str, "cd", ft_strlen(str)) || !ft_strncmp(str, "echo", ft_strlen(str)) ||
		!ft_strncmp(str, "pwd", ft_strlen(str)) ||
		!ft_strncmp(str, "export", ft_strlen(str)) || !ft_strncmp(str, "unset", ft_strlen(str)) || !ft_strncmp(str, "env", ft_strlen(str)) ||
		!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	return (0);
}

int is_sys(t_cmd *cmd)
{
	char *str;
	int i = 0;
	char **env_var;
	char *tmp1;
	char *tmp2;

	str = cmd->c;
	env_var = ft_split(getenv("PATH"), ':');

	while (env_var[i])
	{
		tmp1 = ft_strjoin(env_var[i], "/");
		tmp2 = ft_strjoin(tmp1, str);
		if (!access(tmp2, R_OK))
		{
			// free(tmp1);
			// free(env_var);
			cmd->c_path = tmp2;
			return (1);
		}
		// else
		// {
		// 	free(tmp1);
		// 	free(tmp2);
		// 	free(env_var);
		// }
		i++;
	}
	// while (env_var[i])
	// {
	// 	printf ("%s\n", env_var[i]);
	// 	i ++;
	// }
	return (0);
}

void exe_builtin(t_cmd *cmd)
{
	printf("\"%s\" is a builtin command\n", cmd->c);
}

void exe_sys(t_cmd *cmd)
{
	printf("\"%s\" is a sys command\n", cmd->c);
	if (execve(cmd->c_path, cmd->op, NULL) == -1)
		printf("error in execve");
}

int exe_cmd(t_cmd *cmd, int i, char *cmd_buff, pid_t pid)
{
	if(!ft_strncmp("exit", cmd_buff, ft_strlen(cmd_buff)))
	{
		printf("%d", pid);
		kill(pid, 0);
		return(0);
	}
	else
	while (i < cmd[0].cmd_n)
	{
		if (is_builtin(cmd[i].c))
			exe_builtin(&cmd[i]);
		else if (is_sys(&cmd[i]))
			exe_sys(&cmd[i]);
		else
			printf("\"%s\" is not a command\n", cmd[i].c);
		i++;
	}
	return(1);
}
