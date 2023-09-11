/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:31:58 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 15:21:31 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*key_strdup(char *str)
{
	int		key_len;
	int		i;
	char	*tmp;

	key_len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
		key_len++;
	}
	tmp = (char *)malloc(sizeof(char) * (key_len + 1));
	if (!tmp)
		perror("MALLOC");
	i = -1;
	while (++i < key_len)
		tmp[i] = str[i];
	tmp[i] = '\0';
	return (tmp);
}

static void	exp_strdup_fill(char *add, char *tmp, char *src, int *i)
{
	int	equals_flag;

	equals_flag = 0;
	while (i[0] < (int)ftj_strlen(src) + 13)
	{
		if (i[0] < 11)
			add[i[0]] = tmp[i[0]];
		else
		{
			if (i[0] == (int)ftj_strlen(src) + 13 - 1)
				add[i[0]] = '"';
			else
			{
				add[i[0]] = src[i[1]];
				if (src[i[1]] == '=' && equals_flag == 0)
				{
					add[++i[0]] = '"';
					equals_flag = 1;
				}
			}
			i[1]++;
		}
		i[0]++;
	}
	add[i[0]] = '\0';
}

char	*ft_exp_strdup(char *src)
{
	int		exp_len;
	char	*add;
	char	*tmp;
	int		index[2];

	exp_len = ft_strlen(src) + 13;
	add = (char *)malloc(sizeof(char) * (exp_len + 1));
	if (!add)
		return (0);
	tmp = "declare -x ";
	index[0] = 0;
	index[1] = 0;
	exp_strdup_fill(add, tmp, src, index);
	return (add);
}

char	*ftj_strdup(const char *src)
{
	int		i;
	char	*add;

	i = ft_strlen(src);
	add = (char *)malloc(sizeof(char) * (i + 1));
	if (!add)
		return (0);
	i = 0;
	while (src[i])
	{
		add[i] = src[i];
		i++;
	}
	add[i] = '\0';
	return (add);
}
