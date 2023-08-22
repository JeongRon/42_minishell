/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:07:26 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/22 14:51:01 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** quote를 판단하는 함수
** 현제 char를 읽어서 quote변수를 통해 현재 quote안에 있는지 아닌지 판단해준다.
** int
** 항상 참을 return함
**
** @param		str		문자열 중에서 현제 판단할 문자
** @param		quote	인자로 받아서 문자열에서 읽고 있는 곳을 판단해서 값을 바꾸어 준다.
*/

int	f_q(char str, int *quote)
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

/*
** quote를 판단하는 함수
** 현제 문자열을 읽어서 quote를 제외한 부분들을 c로 나누어서 이중 char **을 만든다.
** char **
** 실패시 NULL을 반환
** 성공시 char **을 반환
**
** @param		str		문자열
** @param		c		구분자
** @param		quote	quote안에 있는 구분자는 구분자로 사용되지 않도록 하는 판단 변수
*/

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
		while ((*str != 0 && *str == c && f_q(*str, &quote)) || quote != 0)
			str++;
		if (*str != 0)
		{
			strings[i] = ft_word((char *)str, c);
			if (check_null(strings, i++))
				return (NULL);
		}
		while ((*str && !(*str == c) && f_q(*str, &quote)) || quote != 0)
			str++;
	}
	strings[i] = 0;
	return (strings);
}
