#include "minishell.h"

void free_cmd(t_cmd *cmd, int i)
{
	while (i < cmd[0].cmd_n)
	{
		if(cmd[i].c)
			free(cmd[i].c);
		// if(cmd[i].c_buf)
		// 	free(cmd[i].c_buf);
		if(cmd[i].c_pre_parse)
			free(cmd[i].c_pre_parse);
		if (cmd[i].re)
		{
			// free_re(cmd[i].re, 0);
			free(cmd[i].re);
		}
		i++;
	}
}

void free_cmd_exit(t_cmd *cmd)
{
    if (cmd)
    {
        free_cmd(cmd, 0);
        free(cmd);
    }
}