/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:42:56 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/31 23:39:25 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *str)
{
	if (!ft_strncmp(str, "cd", ft_strlen(str)) ||
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

int handel_fd(t_cmd *cmd, int i)
{
	t_red *red;

	red = cmd->re;
	while (i < cmd->re_n)
	{
		if (red[i].type == input_redirection)
		{
			if (access(red[i].f_name, F_OK))
			{
				printf("%s: No such file or directory", red[i].f_name);
				return (0);
			}
			else
			{
				// puts("is available");
				// if (cmd->fd_in != 0)
				// 	close(cmd->fd_in);
				cmd->fd_in = open(red[i].f_name, O_RDONLY, 0777);
			}
		}
		else if (red[i].type == output_redirection)
		{
				// if (cmd->fd_out != 1)
				// 	close(cmd->fd_out);
				cmd->fd_out = open(red[i].f_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
		}
		else if (red[i].type == append_redirection)
		{
				// if (cmd->fd_out != 1)
				// 	close(cmd->fd_out);
				cmd->fd_out = open(red[i].f_name, O_RDWR | O_APPEND | O_CREAT, 0777);
		}
		else if (red[i].type == heredoc_redirection && i == cmd->re_n - 1)
		{
			cmd->fd_in = open(red[i].f_name, O_RDWR | O_CREAT | O_TRUNC , 0777);
			write(cmd->fd_in, red[i].str, ft_strlen(red[i].str));
			cmd->fd_in = open(red[i].f_name, O_RDONLY, 0777);
		}
		// printf("filename:%s, type= %d, fd_out=%d, fd_in=%d\n", red[i].f_name, red[i].type, cmd->fd_out, cmd->fd_in);
		
		i++;
	}
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	global_fd_in = cmd->fd_in;
	global_fd_out = cmd->fd_out;
	// if(cmd->pipe_flag_before)
	// {
	// 	cmd->fd_in = 
	// }
	return 1;
}

void exe_builtin(t_cmd *cmd)
{
	printf("\"%s\" is a builtin command\n", cmd->c);
}

void exe_sys(t_cmd *cmd)
{
	// printf("\"%s\" is a sys command\n", cmd->c);
	pid_t pid = fork();
	if (pid == 0){
		handel_fd(cmd, 0);
		execve(cmd->c_path, cmd->op, NULL);		
	}
		
	waitpid(pid, NULL, 0);
	return;
	// if (execve(cmd->c_path, cmd->op, NULL) == -1)
	// 	printf("error in execve");
}

void exe_cmd(t_cmd *cmd, int i, char *cmd_buff)
{
		while (i < cmd[0].cmd_n)
		{
			// if (!handel_fd(&cmd[i], 0))
			// 	return ;
			/*if (is_builtin(cmd[i].c))
				exe_builtin(&cmd[i]);
			else */if (is_sys(&cmd[i]))
				exe_sys(&cmd[i]);
			else
				printf("\"%s\" is not a command\n", cmd[i].c);
			// printf("cmd input:%d, cmd output:%d\n", global_fd_in, global_fd_out);
			i++;
		}
}
