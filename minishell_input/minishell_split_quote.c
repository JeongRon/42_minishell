/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:07:26 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/04 16:56:25 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	f_q(char str, int *quote)
{
	if (str == '\'')
	{
		if (!(*quote))
			(*quote) = -1;
		else if ((*quote) == -1)
			(*quote) = 0;
	}
	if (str == '\"')
	{
		if (!(*quote))
			(*quote) = 1;
		else if ((*quote) == 1)
			(*quote) = 0;
	}
	return (1);
}

static	int	count_strings(char *str, char c)
{
	int	i;
	int	count;
	int	quote;

	quote = 0;
	count = 0;
	i = 0;
	while (str[i] != 0)
	{
		while ((str[i] != 0 && (str[i] == c) \
		&& f_q(str[i], &quote)) || quote != 0)
			i++;
		if (str[i] != 0)
			count++;
		while ((str[i] != 0 && !(str[i] == c) \
		&& f_q(str[i], &quote)) || quote != 0)
			i++;
	}
	return (count);
}

static	char	*ft_word(char *str, char c)
{
	int		len_word;
	int		i;
	int		quote;
	char	*word;

	i = 0;
	quote = 0;
	while ((str[i] != 0 && !(str[i] == c) \
		&& f_q(str[i], &quote)) || quote != 0)
		i++;
	len_word = i;
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
	{
		free(word);
		return (NULL);
	}
	i = 0;
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_quote(char const *str, char c, int quote)
{
	char	**strings;
	int		i;

	if (str == NULL)
		return (NULL);
	i = count_strings((char *)str, c);
	strings = (char **)ft_malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	i = 0;
	while (*str != 0)
	{
		while ((*str != 0 && *str == c && f_q(str[i], &quote)) || quote != 0)
			str++;
		if (*str != 0)
		{
			strings[i] = ft_word((char *)str, c);
			if (check_null(strings, i++))
				return (NULL);
		}
		while ((*str && !(*str == c) && f_q(str[i], &quote)) || quote != 0)
			str++;
	}
	strings[i] = 0;
	return (strings);
}