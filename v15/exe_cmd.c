/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:42:56 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/04 18:59:11 by mjafari          ###   ########.fr       */
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

void exe_builtin(t_cmd *cmd, char **env)
{
	// pid_t pid;
	cmd->data->last_exit_status = 0;
	ft_exit(cmd);
	handel_fd(cmd, 0);
	handel_pipe(cmd);
	ft_cd(cmd);
	cmd->env = env;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	handel_dup2(cmd);
	// 	ft_echo(cmd, 1);
	// 	ft_env(cmd, env);
	// 	ft_pwd(cmd);
	// 	exit(0);
	// }
	// waitpid(pid, NULL, 0);
	return;

	// printf("\"%s\" is a builtin command\n", cmd->c);
}

void exe_sys(t_cmd *cmd)
{
	// printf("dir:%s\n", cmd->data->prev_dir);


		handel_fd(cmd, 0);
		handel_pipe(cmd);
	
	pid_t pid = fork();
	if (pid == 0)
	{
			if (!ft_strncmp(cmd->c, "make", 5))
	{
		close(1);
		close(2);
	}
		// if (!ft_strncmp(cmd->c, "make", 5))
		// {
		// 	close(1);
		// 	close(2);
		// }
		// else
		// {
		// 	handel_fd(cmd, 0);
		// 	handel_pipe(cmd, 0);
		// }
		// char *envp = "PWD=/Users/mjafari/Desktop/school/github/minishell";
		handel_dup2(cmd);
		cmd->data->last_exit_status = execve(cmd->c_path, cmd->op, cmd->env);
	}

	waitpid(pid, NULL, 0);
	return;
	// if (execve(cmd->c_path, cmd->op, NULL) == -1)
	// 	printf("error in execve");
}

void exe_remove(t_data *data, char **env)
{
	t_cmd *remove;

	remove = (t_cmd *)calloc(1, sizeof(t_cmd));
	remove->c = "make";
	remove->op_n = 2;
	remove->re_n = 0;
	remove->cmd_n = 1;
	remove->data = data;
	remove->env = env;

	remove->op = calloc(2, sizeof(char *));
	remove->op[0] = "make";
	remove->op[1] = "remove";
	exe_cmd(remove, 0, env);
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

void exe_cmd(t_cmd *cmd, int i, char **env)
{
	while (i < cmd[0].cmd_n)
	{
		cmd[i].data->prev_dir = ft_strjoin(cmd->data->path, "/");
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
