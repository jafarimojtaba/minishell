#include "minishell.h"

void minishell(char *cmd_buff, t_cmd *cmd, t_data *data, char **env)
{

	cmd[0].data = data;
	cmd_init(cmd, cmd_buff, cmd[0].cmd_n, env);
	pipe_splitter(cmd, cmd_buff, 0, 0);
	dollar_with_q(cmd, 0, 0, 0);
	dollar_no_q(cmd, 0, 0, 0);
	redirection(cmd, 0);
	cmd_c(cmd, cmd[0].cmd_n, 0, 0);
	ft_args_selector(cmd, cmd[0].cmd_n, 0, 0);
	// print_cmd(cmd, cmd_n);
	exe_cmd(cmd, 0);
	data->last_exit_status %= 255;
}