/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:48:15 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 12:53:59 by mjafari          ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>

enum e_redirection_input_output_type
{
	input_redirection = 0,
	output_redirection = 1,
	heredoc_redirection = 3,
	append_redirection = 4,
};

typedef struct s_red
{
	int		id;
	int		red_n;
	int		type;
	char	*f_name;
	char	*str;
}	t_red;

typedef struct s_data
{
	char	path[500];
	char	*path_str;
	char	*prev_dir;
	int		last_exit_status;
	int		cmd_n;
	char	*cmd_buff;
	char	**env;
}	t_data;

typedef struct s_cmd
{
	int				id;
	char			*c_pre_parse;
	char			*c;
	char			*c_path;
	int				op_n;
	char			**op;
	int				pipe_flag_before;
	int				pipe_flag_after;
	char			*pipe_f_name;
	int				pipe_fd;
	int				fd_in;
	int				fd_out;
	int				re_n;
	t_red			*re;
	int				heredoc_id;
	struct s_data	*data;
}	t_cmd;

void	signal_check(int argc, char **argv);

void	data_init(t_data *data, char **env, char *cmd_buff);
void	copy_env(t_data *data, char **env, int i);
char	*ft_getenv(char *str, t_cmd *cmd);

void	dollar_with_q(t_cmd *cmd, int i, int j, int start);
void	dollar_no_q(t_cmd *cmd, int i, int j, int start);
int		dollar_str_env(t_cmd *cmd, int start, int *j, char *first_str);
void	no_dollar_var(t_cmd *cmd, int j, char *first_str);

int		is_q_closed(char *c, int i);
int		find_next_q(char *c, int q, int i);
int		find_next_near_q(char *c, int q, int i);

void	minishell(char *cmd_buff, t_cmd *cmd, t_data *data);
void	exe_remove(char **env);

int		cmd_count(char *c, int i, int count, t_data *data);
void	cmd_init(t_cmd *cmd, t_data *data);
void	cmd_c(t_cmd *cmd, int n, int i, int j);

void	pipe_splitter(t_cmd *t_cmd, char *cmd, int i, int j);

void	ft_args_selector(t_cmd *cmd, int n, int i, int j);
char	*op_q_re(char *c, int i, int start);
char	*remove_start_and_end(char *c, int start, int end);
void	op_count(t_cmd *cmd, int j, int count);
void	op_split(t_cmd *cmd, int i, int j, int start);

void	redirection(t_cmd *cmd, int i);
int		read_n_re(t_cmd *cmd, int j, int count);
int		is_in_or_out_re(char *c, int j);
int		is_output_append(char *c, int j);
char	*find_file_name(char *c, int *j);
char	*remove_f_cmd_pre(char *cmd, int start, int end);
void	update_heredoc_re_vars(t_cmd *cmd, int *id, int *j, int start);
void	update_in_out_re_vars(t_cmd *cmd, int *id, int *j, int start);
void	update_append_re_vars(t_cmd *cmd, int *id, int *j, int start);
void	init_cmd_re(t_cmd *cmd, int i, int j, int id);

int		is_heredoc(char *c, int j);
void	heredoc_input(t_cmd *cmd, int i, int j, int start);
void	heredoc_str(t_cmd *cmd);
char	*ft_new_read(char *dlm, char *ret, int l);

void	exe_cmd(t_cmd *cmd, int i);
int		is_sys(t_cmd *cmd, int i);
int		is_builtin(char *str);
int		handel_fd(t_cmd *cmd, int i);
void	handel_pipe(t_cmd *cmd);
void	handel_dup2(t_cmd *cmd);

void	ft_echo(t_cmd *cmd, int i);
void	ft_cd(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
void	ft_pwd(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
void	ft_export(t_cmd *cmd, int i);
void	ft_unset(t_cmd *cmd);

void	free_cmd_exit(t_cmd *cmd, int end);
void	free_cmd(t_cmd *cmd, int i);
void	free_double_p(void **p);

#endif