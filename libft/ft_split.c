/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjafari <mjafari@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 23:38:50 by mjafari           #+#    #+#             */
/*   Updated: 2022/08/12 13:18:33 by mjafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(const char *s, int c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (i < (int)ft_strlen(s) && s[i] != c)
				i++;
		}
	}
	return (count);
}

static int	ft_end(const char *s, int k, int c)
{
	int	i;

	i = 0;
	if (!(s[k]))
		return (0);
	while (k < (int)ft_strlen(s))
	{
		if (s[k++] == c)
			return (i);
		i++;
	}
	return (i);
}

static void	ft_putarr(char **new_array, char const *s, char c, int count)
{
	int	i;
	int	j;
	int	end;

	i = 0;
	j = 0;
	while (count-- > 0)
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j] && s[j] != c)
		{
			end = ft_end(s, j, c);
			new_array[i] = ft_substr(s, j, end);
			if (!new_array[i])
				free(new_array[i]);
			i++;
			j += end;
		}
	}
	new_array[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**new_array;
	int		count;

	if (!s)
		return (NULL);
	count = ft_counter(s, c);
	new_array = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	new_array[count] = 0;
	ft_putarr(new_array, s, c, count);
	return (new_array);
}
