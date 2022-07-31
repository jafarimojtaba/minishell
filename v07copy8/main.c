/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/29 18:50:14 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *cmd_buff;

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

void minishell(char *cmd_buff, t_cmd *cmd)
{
	int cmd_n;
	int pid;

	cmd_n = cmd_count(cmd_buff, 0, 1);
	cmd = (t_cmd *)calloc(cmd_n, sizeof(t_cmd));
	cmd_init(cmd, cmd_buff, cmd_n);
	pipe_splitter(cmd, cmd_buff, 0, 0);
	dollar_with_q(cmd, 0, 0, 0);
	dollar_no_q(cmd, 0, 0, 0);
	redirection(cmd, 0);
	cmd_c(cmd, cmd_n, 0, 0);
	ft_args_selector(cmd, cmd_n, 0);
	// if(!ft_strncmp("exit", cmd_buff, ft_strlen(cmd_buff)))
	// 	exit(0);

	// pid = fork();
	// if (pid == 0)
	// 	if(!exe_cmd(cmd, 0, cmd_buff, getpid()))
	// 		exit(0);
	// waitpid(pid, NULL, 0);
}

int main(void)
{
	t_cmd *cmd;
	char *cmd_buff;
	int cmd_n;
	int i;
	int j;
	int fd[2];
	pipe(fd);
	// char *temp = "0123456789";

	// printf(ft_substr(temp, 0, 3));
	while (1)
	{
		cmd_buff = readline("MiniShell$ ");
		if (ft_strlen(cmd_buff) > 0)
			add_history(cmd_buff);
		if (!is_q_closed(cmd_buff, 0))
		{
			printf("Please check your input for closed Quotes!\n");
			continue;
		}
		if (!ft_strncmp("exit", cmd_buff, 5))
		{
			free(cmd_buff);
			break;
		}

		minishell(cmd_buff, cmd);

		int fdo= open("outfile", O_WRONLY);
		close(fd[0]);
		dup2(0, fd[1]);
		char *str;
		close(fd[1]);
		read(fd[0], str, 100);
		close(fd[0]);
		write(fdo, str, 100);
		i = 0;
		while (i < cmd_n)
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
// echo hi > f1 | <f3 cat >f2 | wc -c