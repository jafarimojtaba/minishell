/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:23:38 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/14 21:00:03 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_end_before_end(char *cb, int i, char q)
{
	i++;
	while (cb[i] && cb[i] != q)
	{
		if (cb[i] == '\0')
			return (0);
		if (cb[i] == q)
			return (i);
		i++;
	}
	return (i);
}

int check_end_before_pipe(char *cb, int i, char q)
{
	i++;
	while (cb[i] && cb[i] != q)
	{
		if (cb[i] == '\0' || (cb[i] == '|' && cb[i + 1] != '|'))
			return (0);
		if (cb[i] == q)
			return (i);
		i++;
	}
	return (i);
}

int check_end_before_space_or_pipe(char *cb, int i)
{
	i++;
	while (cb[i] && cb[i] != '|' && cb[i] != ' ')
		i++;
	return (i);
}
void	make_command_str(char *begin, char *end, char **splitted)
{
	
}
char **pre_parser(char *commandbuff)
{
	int		i;
	int		end;
	char	**splitted;
	int		s;

	i = 0;
	s = 0;
	while(commandbuff[i])
	{

			i++;
		else if (commandbuff[i] == '\'')
		{
			end = check_end_before_end(commandbuff, i, '\'');
			if (end)
			{
				make_command_str(commandbuff[i], commandbuff[end], splitted);
				i = end;
			}
			else
				return(error_of_not_closing_quotes);
		}
		else if (commandbuff[i] == '"')
		{
			end = check_end_before_pipe(commandbuff, i, '"');
			if (end)
			{
				make_command_str_and_replace_dollar_value(commandbuff[i], commandbuff[end], splitted);
				i = end;
			}
			else
				return(error_of_not_closing_quotes);
		}
		else
		{
			end = check_end_before_space_or_pipe(commandbuff, i);
			if (end)
			{
				make_command_str_and_replace_dollar_value(commandbuff[i], commandbuff[end], splitted);
				i = end;
			}
		}			
	}
	free(commandbuff);
	return(splitted);
}

// int	pipe_counter(char **splitted)
// {
// 	int	i;
// 	int	c;

// 	i = 0;
// 	c = 0;
// 	while (splitted[i])
// 	{
// 		printf("%s\n", splitted[i]);
// 		if (splitted[i][0] == '|' && ft_strlen(splitted[i]) == 1)
// 			c++;
// 		i++;
// 	}
// 	return (c);
// }

// void	ft_make_command(char **splitted, t_com *commands)
// {
// 	int i;
// 	i = 0;

// 	while (splitted[i][0] != '|')
// 	{
// 		/* code */
// 	}
	
// 	//if id = -1 then we can fill that command
// }

// int		ft_search_builtins(char **splitted, int *i, t_com *commands)
// {
// 	int ret;
// 	// ret = ft_strcmp2d(splitted[i], {"echo", "cd", "pwd", "export", "unset", "env", "exit"});
// 	if (ft_strncmp("echo", splitted[*i], ft_strlen(splitted[*i])))
// 		if (ft_strncmp("-n", splitted[*i + 1], ft_strlen(splitted[*i + 1])))
// 			ft_make_command(splitted, *i, commands);
// }

// void	search_commands(char **splitted, int n_pipes, t_com *commands)
// {
// 	int	i;
// 	int	a_ret;
// 	char **b_path;

// 	i = 0;
// 	n_pipes = 0;
// 	b_path = ft_split(getenv("PATH"), ':');
// 	// while (splitted[i])
// 	// {
// 	// 	ft_make_command()
// 	// 	if (!ft_search_builtins(splitted, i, commands))
// 	// 	{
// 	// 		ft_search_shell(splitted[i]);
// 	// 	}
// 	// 	a_ret = access("/bin/echo", R_OK);
// 	// 	printf("access key= %d\n", a_ret);
// 	// 	i++;
// 	// }
// }
