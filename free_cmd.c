#include "minishell.h"

void free_cmd(t_cmd *cmd, int i)
{
	int j;
	while (i < cmd->data->cmd_n)
	{
		if (cmd[i].c_pre_parse)
			free(cmd[i].c_pre_parse);
		if (cmd[i].c)
			free(cmd[i].c);
		if (cmd[i].c_path)
			free(cmd[i].c_path);
		if(cmd[i].pipe_f_name)
			free(cmd[i].pipe_f_name);
		if (cmd[i].re)
		{
			j =  0;
			// printf("red num:%d\n", cmd[i].re_n);
			while (j < cmd[i]. re_n)
			{
				if (cmd[i].re[j].f_name)
					free(cmd[i].re[j].f_name);
				if (cmd[i].re[j].str)
					free(cmd[i].re[j].str);
				j++;
			}
			free(cmd[i].re);
		}
		if (cmd[i].op)
		{
			j = 0;
			while (j <= cmd[i].op_n)
			{
					free((cmd[i].op[j]));
					j++;
			}
			free(cmd[i].op);
		}
		i++;
	}
	free(cmd->data->cmd_buff);
}

void free_data(t_cmd *cmd)
{
	int j;

	j = 0;
	while (cmd->data->env[j])
		free(cmd->data->env[j++]);
	free(cmd->data->env[j]);
	free(cmd->data->env);
	free(cmd->data->prev_dir);
	free(cmd->data->path_str);
	free(cmd->data);
}

void free_cmd_exit(t_cmd *cmd, int end)
{
	if (cmd)
	{
		free_cmd(cmd, 0);
		if (end)
			free_data(cmd);
		free(cmd);
	}
}
