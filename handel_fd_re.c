#include "minishell.h"

int		ft_open(char *s1, char *s2, int o_flag)
{
	char *temp;
	int fd;

	temp = ft_strjoin(s1, s2);
	fd = open(temp, o_flag, 0777);
	free(temp);
	return (fd);
}

void handel_pipe(t_cmd *cmd)
{
	int fd1;
	int fd2;
	char *temp;

	fd1 = 0;
	if (cmd->pipe_flag_after != -1 && cmd->fd_out == 1)
	{
		fd1 = ft_open(cmd->data->path_str, cmd->pipe_f_name, O_RDWR | O_CREAT | O_TRUNC);
		cmd->pipe_fd = fd1;
		cmd->fd_out = fd1;
	}
	if (cmd->pipe_flag_before != -1 && cmd->fd_in == 0)
	{
		temp = ft_strjoin(cmd->data->path_str, cmd[-1].pipe_f_name);
		if (!access(temp, F_OK))
			fd2 = ft_open(cmd->data->path_str, cmd[-1].pipe_f_name, O_RDWR);
		else
			fd2 = ft_open(cmd->data->path_str, cmd[-1].pipe_f_name, O_RDWR | O_CREAT | O_TRUNC);
		cmd->fd_in = fd2;
		free(temp);
	}
}

int handel_fd(t_cmd *cmd, int i)
{
	t_red *red;
	char *temp;

	red = cmd->re;
	while (i < cmd->re_n)
	{
		if (red[i].type == input_redirection)
		{
			temp = ft_strjoin(cmd->data->path_str, red[i].f_name);
			if (access(temp, F_OK))
			{
				printf("%s: No such file or directory\n", red[i].f_name);
				free(temp);
				return (0);
			}
			else
				cmd->fd_in = ft_open(cmd->data->path_str, red[i].f_name, O_RDONLY );
			free(temp);
		}
		else if (red[i].type == output_redirection)
			cmd->fd_out = ft_open(cmd->data->path_str, red[i].f_name, O_RDWR | O_CREAT | O_TRUNC);
		else if (red[i].type == append_redirection)
			cmd->fd_out = ft_open(cmd->data->path_str, red[i].f_name, O_RDWR | O_APPEND | O_CREAT);
		else if (red[i].type == heredoc_redirection)
		{
			cmd->fd_in = ft_open(cmd->data->path_str, red[i].f_name, O_RDWR | O_CREAT | O_TRUNC);
			write(cmd->fd_in, red[i].str, ft_strlen(red[i].str));
			cmd->fd_in = ft_open(cmd->data->path_str, red[i].f_name, O_RDONLY);
		}
		i++;
	}
	return 1;
}

void handel_dup2(t_cmd *cmd)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
}