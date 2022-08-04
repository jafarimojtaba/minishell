#include "minishell.h"

void handel_pipe(t_cmd *cmd)
{
	int fd1;
	int fd2;

	fd1 = 0;
	if (cmd->pipe_flag_after != -1 && cmd->fd_out == 1)
	{
		fd1 = open(ft_strjoin(cmd->data->prev_dir, cmd->pipe_f_name), O_RDWR | O_CREAT | O_TRUNC, 0777);
		cmd->pipe_fd = fd1;
		// dup2(fd1, STDOUT_FILENO);
		cmd->fd_out = fd1;
	}
	// printf("pipeflag after:%d",cmd->pipe_flag_after);
	if (cmd->pipe_flag_before != -1 && cmd->fd_in == 0)
	{
		// printf("%s\n", cmd[-1].pipe_f_name);
		// close(cmd[-1].pipe_fd);
		if (!access(ft_strjoin(cmd->data->prev_dir, cmd[-1].pipe_f_name), F_OK))
			fd2 = open(ft_strjoin(cmd->data->prev_dir, cmd[-1].pipe_f_name), O_RDWR, 0777);
		else
			fd2 = open(ft_strjoin(cmd->data->prev_dir, cmd[-1].pipe_f_name), O_RDWR | O_CREAT | O_TRUNC, 0777);

		// dup2(fd2, STDIN_FILENO);
		cmd->fd_in = fd2;
	}
}

int handel_fd(t_cmd *cmd, int i)
{
	t_red *red;

	red = cmd->re;
	while (i < cmd->re_n)
	{
		if (red[i].type == input_redirection)
		{
			if (access(ft_strjoin(cmd->data->prev_dir, red[i].f_name), F_OK))
			{
				printf("%s: No such file or directory", red[i].f_name);
				return (0);
			}
			else
			{
				// puts("is available");
				// if (cmd->fd_in != 0)
				// 	close(cmd->fd_in);
				printf("dir2:%s\n", ft_strjoin(cmd->data->prev_dir, red[i].f_name));

				cmd->fd_in = open(ft_strjoin(cmd->data->prev_dir, red[i].f_name), O_RDONLY, 0777);
				printf("fd=%d\n", cmd->fd_in);
			}
		}
		else if (red[i].type == output_redirection)
		{
			// if (cmd->fd_out != 1)
			// 	close(cmd->fd_out);
			printf("dir2:%s\n", ft_strjoin(cmd->data->prev_dir, red[i].f_name));
			cmd->fd_out = open(ft_strjoin(cmd->data->prev_dir, red[i].f_name), O_RDWR | O_CREAT | O_TRUNC, 0777);
			printf("fd=%d\n", cmd->fd_out);
		}
		else if (red[i].type == append_redirection)
		{
			// if (cmd->fd_out != 1)
			// 	close(cmd->fd_out);
			cmd->fd_out = open(ft_strjoin(cmd->data->prev_dir, red[i].f_name), O_RDWR | O_APPEND | O_CREAT, 0777);
		}
		else if (red[i].type == heredoc_redirection)
		{
			cmd->fd_in = open(ft_strjoin(cmd->data->prev_dir, red[i].f_name), O_RDWR | O_CREAT | O_TRUNC, 0777);
			write(cmd->fd_in, red[i].str, ft_strlen(red[i].str));
			cmd->fd_in = open(ft_strjoin(cmd->data->prev_dir, red[i].f_name), O_RDONLY, 0777);
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

void handel_dup2(t_cmd *cmd)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	global_fd_in = cmd->fd_in;
	global_fd_out = cmd->fd_out;
}