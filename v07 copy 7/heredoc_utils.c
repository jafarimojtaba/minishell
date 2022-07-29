/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:22:41 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/26 12:03:04 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_new_read(char *dlm, char *ret, int l)
{
	char	*rl;
	char	*temp;

	rl = ft_strjoin(dlm, "hi");
	while (ft_strncmp(dlm, rl, ft_strlen(rl) + 1) != 0)
	{
		if (rl && !l)
			free(rl);
		rl = readline(">");
		if (ft_strncmp(dlm, rl, ft_strlen(rl) + 1) != 0)
		{
			temp = ret;
			ret = ft_strjoin(ret, rl);
			if (temp && l)
				free(temp);
			temp = ret;
			ret = ft_strjoin(ret, "\n");
			free(temp);
			free(rl);
			l++;
		}
	}
	if (rl)
		free(rl);
	return (ret);
}

int	is_heredoc(char *c, int j)
{
	if ((c[j] == '<' && c[j + 1] == '<' && !ft_strchr("<>", c[j + 2])
			&& !ft_strchr("<>", c[j - 1]) && j)
		|| (c[j] == '<' && c[j + 1] == '<'
			&& !ft_strchr("<>", c[j + 2]) && !j))
		return (1);
	else
		return (0);
}

int	heredoc_str(t_cmd *cmd, char *first_str, int start, int j)
{
	char	*temp0;
	char	*temp1;

	temp0 = ft_substr(cmd->c_pre_parse, start, j - start);
	temp1 = ft_new_read(temp0, "", 0);
	free(temp0);
	temp0 = ft_strjoin(temp1, "'");
	free(temp1);
	temp1 = ft_strjoin("'", temp0);
	free(temp0);
	temp0 = ft_strjoin(first_str, temp1);
	free(temp1);
	free(first_str);
	temp1 = ft_strjoin(temp0, &cmd->c_pre_parse[j]);
	free(cmd->c_pre_parse);
	cmd->c_pre_parse = temp1;
	j = ft_strlen(temp0);
	free(temp0);
	return (j);
}
