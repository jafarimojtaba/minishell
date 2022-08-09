#include "minishell.h"

void print_cmd(t_cmd *cmd, int n)
{
	int i = 0;
	int j;
	printf("in print cmd%d", n);
	while (i < n)
	{
		// printf("PIPE_before = %d, PIPE_after = %d PP_CMD : %s$\n",commands[i].pipe_flag_before, commands[i].pipe_flag_after, commands[i].c_pre_parse);
		puts("------------------------------------------------");
		printf("CMD_PP:%s#\n", cmd[i].c_pre_parse);
		printf("CMD:%s#\n", cmd[i].c);
		puts("");
		j = 0;
		while (j < cmd[i].op_n)
		{
			printf("op %d=%s#\n", j, cmd[i].op[j]);
			j++;
		}
		puts("");
		j = 0;
		while (j < cmd[i].re_n)
		{
			printf("re %d=\ttype=%d\tfname=%s\tstr=%s#\n", cmd[i].re[j].id, cmd[i].re[j].type, cmd[i].re[j].f_name, cmd[i].re[j].str);
			j++;
		}
		puts("");
		i++;
	}
}

void minishell(char *cmd_buff, t_cmd *cmd, t_data *data, char **env)
{

	cmd[0].data = data;
	cmd_init(cmd, cmd_buff, cmd[0].cmd_n, env);
	pipe_splitter(cmd, cmd_buff, 0, 0);
	dollar_no_q(cmd, 0, 0, 0);
	dollar_with_q(cmd, 0, 0, 0);
	redirection(cmd, 0);
	cmd_c(cmd, cmd[0].cmd_n, 0, 0);
	ft_args_selector(cmd, cmd[0].cmd_n, 0, 0);
	// print_cmd(cmd, cmd[0].cmd_n);
	exe_cmd(cmd, 0);
	data->last_exit_status %= 255;
}