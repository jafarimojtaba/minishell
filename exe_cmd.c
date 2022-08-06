/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:42:56 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/06 00:41:08 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *str)
{
	if (!ft_strncmp(str, "cd", ft_strlen(str) + 3) ||
		!ft_strncmp(str, "echo", ft_strlen(str) + 5) ||
		!ft_strncmp(str, "pwd", ft_strlen(str) + 4) ||
		!ft_strncmp(str, "export", ft_strlen(str) + 7) ||
		!ft_strncmp(str, "unset", ft_strlen(str) + 6) ||
		!ft_strncmp(str, "env", ft_strlen(str) + 4) ||
		!ft_strncmp(str, "exit", ft_strlen(str) + 5))
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

	if (!access(cmd->c, R_OK))
	{
		cmd->c_path = cmd->c;
		return 1;
	}
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
	pid_t pid;
	cmd->data->last_exit_status = 0;
	ft_exit(cmd);
	if (!handel_fd(cmd, 0))
	{
		cmd->data->last_exit_status = 1;
		return;
	}
	handel_pipe(cmd);
	ft_cd(cmd);
	ft_export(cmd, 1);
	pid = fork();
	if (pid == 0)
	{
		handel_dup2(cmd);
		ft_env(cmd);
		ft_echo(cmd, 1);
		ft_pwd(cmd);
		exit(0);
	}

	waitpid(pid, NULL, 0);
	return;
	// printf("\"%s\" is a builtin command\n", cmd->c);
}

void exe_sys(t_cmd *cmd)
{
	if (!handel_fd(cmd, 0))
	{
		cmd->data->last_exit_status = 1;
		return;
	}
	handel_pipe(cmd);
	pid_t pid = fork();
	if (pid == 0)
	{
		handel_dup2(cmd);
		execve(cmd->c_path, cmd->op, cmd->env);
	}
	waitpid(pid, &cmd->data->last_exit_status, 0);
	return;
}

void exe_remove(char **env)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		char *remove_cmd[] = {"/bin/sh", "-c", "rm -f mini_temp*", NULL};
		execve("/bin/sh", remove_cmd, env);
	}
	waitpid(pid, NULL, 0);
}

void exe_cmd(t_cmd *cmd, int i)
{
	while (i < cmd[0].cmd_n)
	{
		cmd[i].data->prev_dir = ft_strjoin(cmd->data->path, "/");
		if (is_builtin(cmd[i].c))
			exe_builtin(&cmd[i]);
		else if (is_sys(&cmd[i]))
			exe_sys(&cmd[i]);
		else
		{
			printf("\"%s\" is not a command\n", cmd[i].c);
			cmd[i].data->last_exit_status = 127;
		}
		// printf("cmd input:%d, cmd output:%d\n", global_fd_in, global_fd_out);
		i++;
	}
}
