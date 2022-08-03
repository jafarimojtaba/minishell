/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/03 17:56:10 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *cmd_buff;
int gflag = 0;

void print_split(char **sp)
{
	int i;

	i = 0;
	while (sp[i])
	{
		printf("%s\n", sp[i]);
		i++;
	}
}

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
	int cmd_n;

	cmd_n = cmd_count(cmd_buff, 0, 1);
	cmd = (t_cmd *)calloc(cmd_n, sizeof(t_cmd));
	cmd[0].data = data;
	cmd_init(cmd, cmd_buff, cmd_n, env);
	pipe_splitter(cmd, cmd_buff, 0, 0);
	dollar_with_q(cmd, 0, 0, 0);
	dollar_no_q(cmd, 0, 0, 0);
	redirection(cmd, 0);
	cmd_c(cmd, cmd_n, 0, 0);
	ft_args_selector(cmd, cmd_n, 0, 0);
	// print_cmd(cmd, cmd_n);
	exe_cmd(cmd, 0, cmd_buff, env);
}

// void sigintHandler(int sig_num)
// {
//     // signal(SIGINT, sigintHandler);
//     // printf("\n Cannot be terminated using Ctrl+C \n");
//     // gflag = 1;
// 	// rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	rl_on_new_line();
// 	rl_redisplay();
// 	// printf("\b\b  \n");
// }

int main(int argc, char **argv, char **env)
{
	// struct sigaction sa;

	t_cmd *cmd;
	t_data *data;
	char *cmd_buff;
	int i;
	int j;
	
	data = calloc(1, sizeof(t_data));
	data->last_exit_status = 0;
	// sa.sa_sigaction = sigintHandler;
	// sa.sa_flags = SA_SIGINFO;
	// sigaction(SIGINT, &sa, NULL);
	// signal(SIGINT, sigintHandler);
	// 	i = 0;
	while (1)
	{
		// signal(SIGINT, sigintHandler);
		// if(gflag)
		// {
		// 	gflag = 0;
		// 	puts("hi");
		// 	continue;
		// }
		exe_remove();
		cmd_buff = readline("MiniShell$ ");
		if (ft_strlen(cmd_buff) > 0)
			add_history(cmd_buff);
		else
			continue;
		if (!is_q_closed(cmd_buff, 0))
		{
			printf("Please check your input for closed Quotes!\n");
			continue;
		}
		if (!ft_strncmp("exit", cmd_buff, ft_strlen(cmd_buff) + 5))
		{
			free(cmd_buff);
			break;
		}
		minishell(cmd_buff, cmd, data, env);
		// if (cmd)
		// {
		// 	free_cmd(cmd, 0);
		// 	free(cmd);
	}
	return (0);
}

// <f0 echo hi >f1 how >f2 >f3 are you >f4
// echo hi  how   are you
//  echo hi  how   are you
//   echo hi  how   are you
// <f0 echo hi >f1 how >f2 >f3 are you >f4 |>f7 >f8 grep hi <f9
// echo hi how are you|grep hi
// <f0 echo hi >f1 how >f2 >f3 are you  >f4 |>f7 >f8 grep hi <f9 "hh$USER" << mj to
// "hi from test"|'|"'
// echo hi | grep how | <<mj cat "$USERj"| also $PAT"$PATH"
// echo hi >f1"how$USER"

// echo "$USER" hi"$USER"       nhj | sdf dfgh

// echo "$USER" hi"$USER"       nhj | sdf dfgh

// MiniShell$ <<mj cat > f1| grep hi
// dlm=mj#
// >hkjkjhsv
// >hi
// >mj
// cat: '': No such file or directory
// hi mj
// MiniShell$ 
