/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:02:31 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 14:16:50 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_q_var(char *temp1, char **dollar_str, t_cmd *cmd)
{
	if (!ft_strncmp(*dollar_str, "?", ft_strlen(*dollar_str)))
	{
		temp1 = *dollar_str;
		*dollar_str = ft_itoa(cmd->data->last_exit_status);
		free(temp1);
		return (1);
	}
	return (0);
}

int	dollar_str_env(t_cmd *cmd, int start, int *j, char *first_str)
{
	char	*temp1;
	char	*temp2;
	char	*dollar_str;

	temp1 = NULL;
	(*j)++;
	dollar_str = ft_substr(cmd->c_pre_parse, start, *j - start);
	if (!if_q_var(temp1, &dollar_str, cmd))
	{
		temp1 = dollar_str;
		dollar_str = ft_getenv(dollar_str, cmd);
		free(temp1);
	}
	if (ft_strlen(dollar_str))
	{
		temp1 = ft_strjoin(first_str, dollar_str);
		free(first_str);
		free(dollar_str);
		temp2 = ft_strjoin(temp1, &cmd->c_pre_parse[*j]);
		free(temp1);
		free(cmd->c_pre_parse);
		cmd->c_pre_parse = temp2;
		return (1);
	}
	return (0);
}

void	no_dollar_var(t_cmd *cmd, int j, char *first_str)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(first_str, "");
	free(first_str);
	temp2 = ft_strjoin(temp1, &cmd->c_pre_parse[j]);
	free(temp1);
	free(cmd->c_pre_parse);
	cmd->c_pre_parse = temp2;
}

void	copy_env(t_data *data, char **env, int i)
{
	char	**env_dup;
	char	buf[500];

	while (env[i])
		i++;
	env_dup = (char **)malloc((i + 2) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		env_dup[i] = ft_strdup(env[i]);
		i++;
	}
	env_dup[i] = ft_strjoin("OLDPWD=", getcwd(buf, 500));
	env_dup[i + 1] = NULL;
	data->env = env_dup;
}
