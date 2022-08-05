/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:48:15 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/05 21:30:39 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "./libft/libft.h"
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>

enum redirection_input_output_type
{
	input_redirection = 0,
	output_redirection = 1,
	heredoc_redirection = 3,
	append_redirection = 4,
};

typedef struct s_red
{
	int id;
	int red_n;
	int type;
	char *f_name;
	char *str;
} t_red;

typedef struct s_data
{
	char	path[500];
	char    *path_str;
	char	*prev_dir;
	int 	last_exit_status;
}t_data;

typedef struct s_cmd
{
	int id;
	char *c_buf;
	char *c_pre_parse;
	int cmd_n;
	char *c;
	char *c_path;
	int op_n;
	char **op;
	int pipe_flag_before;
	int pipe_flag_after;
	char *pipe_f_name;
	int pipe_fd;
	int fd_in;
	int fd_out;
	int re_n;
	t_red *re;
	int heredoc_id;
	char **env;
	int exit_status;
	struct s_data *data;
} t_cmd;

// first read number of redirections and malloc for the size of s_red pointer;
void minishell(char *cmd_buff, t_cmd *cmd, t_data *data, char **env);

char **split_command(char *cb);
int cmd_num(char *cmd);
void data_init(t_data *data);

void signal_check();
void free_cmd_exit(t_cmd *cmd);

void handel_pipe(t_cmd *cmd);
int handel_fd(t_cmd *cmd, int i);
void handel_dup2(t_cmd *cmd);

// void cmd_fill(t_cmd *cmd_s, char *cmd);
void cmd_init(t_cmd *cmd, char *cmd_buff, int n, char **env);
void cmd_c(t_cmd *cmd, int n, int i, int j);
int cmd_count(char *c, int i, int count);
void pipe_splitter(t_cmd *t_cmd, char *cmd, int i, int j);
void dollar_with_q(t_cmd *cmd, int i, int j, int start);
void dollar_no_q(t_cmd *cmd, int i, int j, int start);
void heredoc_input(t_cmd *cmd, int i, int j, int start);
void redirection(t_cmd *cmd, int i);
char *find_file_name(char *c, int *j);
void ft_args_selector(t_cmd *cmd, int n, int i, int j);
int find_next_q(char *c, int q, int i);
int is_q_closed(char *c, int i);
char *remove_f_cmd_pre(char *cmd, int start, int end);
void free_cmd(t_cmd *cmd, int i);
int is_heredoc(char *c, int j);
void heredoc_str(t_cmd *cmd);
char *ft_new_read(char *dlm, char *ret, int l);
int dollar_str_env(t_cmd *cmd, int start, int *j, char *first_str);
void no_dollar_var(t_cmd *cmd, int j, char *first_str);
int read_n_re(t_cmd *cmd, int j, int count);
int is_in_or_out_re(char *c, int j);
int is_output_append(char *c, int j);
int is_heredoc(char *c, int j);
void exe_cmd(t_cmd *cmd, int i, char **env);
int find_next_near_q(char *c, int q, int i);
void exe_remove(char **env);

void ft_echo(t_cmd *cmd, int i);
int handel_fd(t_cmd *cmd, int i);
// void handel_pipe(t_cmd *cmd, int i);
void ft_env(t_cmd *cmd, char **env);
void ft_pwd(t_cmd *cmd);
void ft_exit(t_cmd *cmd);
void ft_cd(t_cmd *cmd);
void handel_dup2(t_cmd *cmd);

#endif