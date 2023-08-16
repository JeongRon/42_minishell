/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:45:31 by dongmiki          #+#    #+#             */
/*   Updated: 2023/07/29 17:22:10 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_null(char **str, int count)
{
	int	index;

	if (str[count] != NULL)
		return (0);
	index = 0;
	while (index < count)
		free(str[index++]);
	free(str);
	return (1);
}

static	int	count_strings(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != 0)
	{
		while (str[i] != 0 && (str[i] == c))
			i++;
		if (str[i] != 0)
			count++;
		while (str[i] != 0 && !(str[i] == c))
			i++;
	}
	return (count);
}

static	int	ft_strlen_sep(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != 0 && !(str[i] == c))
		i++;
	return (i);
}

static	char	*ft_word(char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen_sep(str, c);
	word = (char *)malloc(sizeof(char) * (len_word +1));
	if (!word)
	{
		free(word);
		return (NULL);
	}
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *str, char c)
{
	char	**strings;
	int		i;

	if (str == NULL)
		return (NULL);
	i = count_strings((char *)str, c);
	strings = (char **)malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	i = 0;
	while (*str != 0)
	{
		while (*str != 0 && *str == c)
			str++;
		if (*str != 0)
		{
			strings[i] = ft_word((char *)str, c);
			if (check_null(strings, i++))
				return (NULL);
		}
		while (*str && !(*str == c))
			str++;
	}
	strings[i] = 0;
	return (strings);
}
