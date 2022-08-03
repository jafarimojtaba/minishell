/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:46:35 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/03 17:53:20 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_cmd *cmd)
{
	if (ft_strncmp(cmd->c, "cd", ft_strlen(cmd->c)+ 3))
		return ;
	// char *write_cmd[] = { "/bin/sh", "-c", "cd ..", NULL };
	// execve("/bin/sh", write_cmd, NULL);
	// chdir("..");
	char s[100];
  
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
  
    // using the command
	// opendir()
    chdir("..");
    chdir("..");
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
  
    // after chdir is executed
    // return 0;
	
}
