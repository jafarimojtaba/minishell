/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:42:56 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/03 18:18:53 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *str)
{
	if (!ft_strncmp(str, "cd", ft_strlen(str)+ 3) ||
		!ft_strncmp(str, "echo", ft_strlen(str)+ 5) ||
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
		else if (red[i].type == heredoc_redirection)
		{
			cmd->fd_in = open(red[i].f_name, O_RDWR | O_CREAT | O_TRUNC , 0777);
			write(cmd->fd_in, red[i].str, ft_strlen(red[i].str));
			cmd->fd_in = open(red[i].f_name, O_RDONLY, 0777);
		}
		// printf("filename:%s, type= %d, fd_out=%d, fd_in=%d\n", red[i].f_name, red[i].type, cmd->fd_out, cmd->fd_in);
		
		i++;
	}
	// if (!f)
	// {
	// dup2(cmd->fd_in, STDIN_FILENO);
	// dup2(cmd->fd_out, STDOUT_FILENO);
	// global_fd_in = cmd->fd_in;
	// global_fd_out = cmd->fd_out;
	// }
	// else
	// 	close(1);
	// if(cmd->pipe_flag_before)
	// {
	// 	cmd->fd_in = 
	// }
	return 1;
}

void exe_builtin(t_cmd *cmd, char **env)
{
	pid_t pid;
	
	ft_exit(cmd);
	pid = fork();
	if (pid == 0)
	{
		handel_fd(cmd, 0);
		handel_pipe(cmd, 0);
		ft_echo(cmd, 1);
		ft_env(cmd, env);
		ft_pwd(cmd);
		ft_cd(cmd);
		exit(0);
	}
	cmd->data->last_exit_status = 0;
	waitpid(pid, NULL, 0);
	return;

	// printf("\"%s\" is a builtin command\n", cmd->c);
}
void handel_pipe(t_cmd *cmd, int i)
{
	int fd1;
	int fd2;

	fd1 = 0;
	if (cmd->pipe_flag_after != -1 && cmd->fd_out == 1)
	{
		fd1 = open(cmd->pipe_f_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
		cmd->pipe_fd = fd1;
		// dup2(fd1, STDOUT_FILENO);
		cmd->fd_out = fd1;
	}
	// printf("pipeflag after:%d",cmd->pipe_flag_after);
	if (cmd->pipe_flag_before != -1 && cmd->fd_in == 0)
	{
		// printf("%s\n", cmd[-1].pipe_f_name);
		// close(cmd[-1].pipe_fd);
		if(!access(cmd[-1].pipe_f_name, F_OK))
			fd2 = open(cmd[-1].pipe_f_name, O_RDWR, 0777);
		else
			fd2 = open(cmd[-1].pipe_f_name, O_RDWR | O_CREAT | O_TRUNC, 0777);

			// dup2(fd2, STDIN_FILENO);
			cmd->fd_in = fd2;
	}
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	global_fd_in = cmd->fd_in;
	global_fd_out = cmd->fd_out;
}
void exe_sys(t_cmd *cmd)
{
	// printf("\"%s\" is a sys command\n", cmd->c);
	pid_t pid = fork();
	if (pid == 0){
		if (!ft_strncmp(cmd->c, "make", 5))
		{
			close(1);
			close(2);
		}
		else
		{
			handel_fd(cmd, 0);
			handel_pipe(cmd, 0);
		}
		cmd->data->last_exit_status = execve(cmd->c_path, cmd->op, NULL);
	}
		
	waitpid(pid, NULL, 0);
	return;
	// if (execve(cmd->c_path, cmd->op, NULL) == -1)
	// 	printf("error in execve");
}

void exe_remove(void)
{
	t_cmd *remove;

	remove = (t_cmd *)calloc(1, sizeof(t_cmd));
	remove->c = "make";
	remove->op_n = 2;
	remove->re_n = 0;
	remove->cmd_n = 1;
	
	remove->op = calloc(2 , sizeof(char *));
	remove->op[0] = "make";
	remove->op[1] = "remove";
	exe_cmd(remove, 0, NULL, NULL);
}

// void exe_rename(void)
// {
// 	t_cmd *rename;

// 	rename = (t_cmd *)calloc(1, sizeof(t_cmd));
// 	rename->c = "make";
// 	rename->op_n = 2;
// 	rename->re_n = 0;
// 	rename->cmd_n = 1;
	
// 	rename->op = calloc(2 , sizeof(char *));
// 	rename->op[0] = "make";
// 	rename->op[1] = "rename";
// 	exe_cmd(rename, 0, NULL);
// }

void exe_cmd(t_cmd *cmd, int i, char *cmd_buff, char **env)
{
		while (i < cmd[0].cmd_n)
		{
			// if (!handel_fd(&cmd[i], 0))
			// 	return ;
			if (is_builtin(cmd[i].c))
				exe_builtin(&cmd[i], env);
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
