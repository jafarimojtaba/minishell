/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 18:48:00 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/11 11:04:05 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_new_read(char *dlm, char *ret, int l)
{
	char	*rl;
	char	*temp;
	char	*temp2 = NULL;

	rl = ft_strjoin(dlm, "hi");
	// printf("dlm=%s#\n", dlm);
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
			if (temp)
				free(temp);
			l++;
		}
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
	char	*temp;

	temp = ft_new_read(cmd->re[cmd->heredoc_id].f_name, "", 0);

	cmd->re[cmd->heredoc_id].str = temp;
}
