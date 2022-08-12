/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 18:48:00 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 12:56:01 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_read_p2(char **temp, char **ret, int *l, char **rl)
{
	*temp = *ret;
	*ret = ft_strjoin(*ret, *rl);
	if (*temp && *l)
		free(*temp);
	*temp = *ret;
	*ret = ft_strjoin(*ret, "\n");
	if (*temp)
		free(*temp);
	(*l)++;
}

char	*ft_new_read(char *dlm, char *ret, int l)
{
	char	*rl;
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	rl = ft_strjoin(dlm, "hi");
	while (ft_strncmp(dlm, rl, ft_strlen(rl) + 1) != 0)
	{
		if (rl && !l)
			free(rl);
		rl = readline(">");
		if (ft_strncmp(dlm, rl, ft_strlen(rl) + 1) != 0)
			ft_new_read_p2(&temp, &ret, &l, &rl);
		if (temp2)
			free(temp2);
		temp2 = rl;
	}
	if (rl)
		free(rl);
	return (ret);
}

int	is_heredoc(char *c, int j)
{
	if ((c[j] == '<' && c[j + 1] == '<' && !ft_strchr("<>", c[j + 2])
			&& j && !ft_strchr("<>", c[j - 1]))
		|| (c[j] == '<' && c[j + 1] == '<'
			&& !ft_strchr("<>", c[j + 2]) && !j))
		return (1);
	else
		return (0);
}

void	heredoc_str(t_cmd *cmd)
{
	t_cmd	*cmd_temp;
	t_data	*data_temp;

	cmd_temp = (t_cmd *)malloc(sizeof(t_cmd));
	data_temp = (t_data *)malloc(sizeof(t_data));
	cmd_temp->c_pre_parse = ft_new_read(cmd->re[cmd->heredoc_id].f_name, "", 0);
	cmd_temp->data = data_temp;
	data_temp->cmd_n = 1;
	data_temp->env = cmd->data->env;
	dollar_no_q(cmd_temp, 0, 0, 0);
	dollar_with_q(cmd_temp, 0, 0, 0);
	cmd->re[cmd->heredoc_id].str = cmd_temp->c_pre_parse;
	free(cmd_temp);
	free(data_temp);
}
