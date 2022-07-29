/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:48:15 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/15 20:59:07 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "./libft/libft.h"
# include <fcntl.h>

typedef struct	s_cmd
{
	int			id;
	int			end_of_c;
	char		*c_pre_parse;
	int			pipe_flag_before;
	int			pipe_flag_after;
	char		*c;
	char		**op;
	int			fd_in;
	int			fd_out;
} 				t_cmd;

char **split_command(char *cb);
int cmd_num(char *cmd);
void cmd_fill(t_cmd *cmd_s, char *cmd);
void cmd_init(t_cmd *cmd, int n);
void cmd_c(t_cmd *cmd, int n);

#endif