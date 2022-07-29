/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:48:15 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/12 21:25:34 by mjafari          ###   ########.fr       */
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

typedef struct	s_com
{
	int			id;
	int			id_last_created;
	int			pr;
	char		*c_pre_parse;
	int			pipe_flag_before;
	int			pipe_flag_after;
	char		*c;
	char		**op;
	int			fd_in;
	int			fd_out;
} 				t_com;

void	ft_env(char **env, int fd);
char	**parser(char *commandbuff);
void	free_splitted(char **splitted);
int		pipe_counter(char **splitted);
void	create_commands(char **splitted, int n_pipes);

#endif