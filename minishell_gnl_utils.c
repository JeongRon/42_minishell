/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:54:36 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 19:20:45 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char *a, char *b)
{
	free(a);
	free(b);
}

int	ft_linelen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*gnl_strjoin(char *buff, char *tmp, int tmp_len)
{
	char	*join_buff;
	int		buff_len;
	int		i;

	buff_len = ft_strlen(buff);
	join_buff = (char *)malloc(sizeof(char) * (buff_len + tmp_len + 1));
	if (!join_buff)
		return (NULL);
	i = 0;
	while (i < buff_len)
	{
		join_buff[i] = buff[i];
		i++;
	}	
	i = 0;
	while (i < tmp_len)
	{
		join_buff[buff_len + i] = tmp[i];
		i++;
	}
	join_buff[buff_len + i] = '\0';
	free(buff);
	return (join_buff);
}
