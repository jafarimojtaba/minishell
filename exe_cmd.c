/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:42:56 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/13 13:31:10 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_builtin(t_cmd *cmd)
{
	pid_t	pid;

	cmd->data->last_exit_status = 0;
	ft_exit(cmd);
	if (!handel_fd(cmd, 0))
	{
		cmd->data->last_exit_status = 1;
		return ;
	}
	handel_pipe(cmd);
	ft_cd(cmd);
	ft_export(cmd, 1);
	ft_unset(cmd);
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
	return ;
}

int	special_cat(t_cmd *cmd)
{
	if (cmd->fd_in == 0 && cmd->pipe_flag_before == -1)
	{
		cmd->pipe_flag_after = -1;
		if (cmd->id < cmd->data->cmd_n - 1)
			cmd[1].pipe_flag_before = -1;
		return (1);
	}
	return (0);
}

void	exe_sys(t_cmd *cmd)
{
	pid_t	pid;

	if (!handel_fd(cmd, 0))
	{
		cmd->data->last_exit_status = 1;
		return ;
	}
	handel_pipe(cmd);
	if (!ft_strncmp(cmd->c, "cat", ft_strlen(cmd->c) + 1) && special_cat(cmd))
	{
		cmd->data->last_exit_status = 1;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		handel_dup2(cmd);
		execve(cmd->c_path, cmd->op, cmd->data->env);
	}
	waitpid(pid, &cmd->data->last_exit_status, 0);
	return ;
}

void	exe_remove(char **env)
{
	int		pid;
	char	*remove_cmd[4];

	pid = fork();
	if (pid == 0)
	{
		remove_cmd[0] = "/bin/sh";
		remove_cmd[1] = "-c";
		remove_cmd[2] = "rm -f mini_temp*";
		remove_cmd[3] = NULL;
		execve("/bin/sh", remove_cmd, env);
	}
	waitpid(pid, NULL, 0);
}

void	exe_cmd(t_cmd *cmd, int i)
{
	while (i < cmd->data->cmd_n)
	{
		if (!ft_strlen(cmd[i].c))
		{
			printf("Empty command\n");
			cmd[i].data->last_exit_status = 127;
		}
		else if (is_builtin(cmd[i].c))
			exe_builtin(&cmd[i]);
		else if (is_sys(&cmd[i], 0))
			exe_sys(&cmd[i]);
		else
		{
			printf("\"%s\" is not a command\n", cmd[i].c);
			cmd[i].data->last_exit_status = 127;
		}
		i++;
	}
}
