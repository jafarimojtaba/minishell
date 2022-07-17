/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:37:12 by mjafari           #+#    #+#             */
/*   Updated: 2022/07/16 20:58:35 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *dollar_var(char *cmd)
{
	int end;
	while (*cmd)
	{
		if (*cmd == '\'')
		{
			cmd++;
			while (*cmd && *cmd != '\'')
				cmd++;
			if (!(*cmd))
			{
				printf("no closing quotes, dollar.c l:23");
				exit(1);
			}
		}
		if (*cmd == '"')
		{
			cmd++;
		}
	}
	
}