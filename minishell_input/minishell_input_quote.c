/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:35:30 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/16 16:40:46 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*ft_strjoinl(char *s1, char *s2)
// {
// 	char		*str;
// 	size_t		len1;
// 	size_t		len2;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	str = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
// 	if (!str)
// 		return (NULL);
// 	ft_memcpy(str, (char *)s1, len1);
// 	str[len1] = '\n';
// 	ft_memcpy(str + len1 + 1, (char *)s2, len2);
// 	str[len1 + len2 + 1] = '\0';
// 	free(s1);
// 	free(s2);
// 	return (str);
// }

static void	find_quote(char *str, int i, int *quote)
{
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (!(*quote))
				(*quote) = -1;
			else if ((*quote) == -1)
				(*quote) = 0;
		}
		if (str[i] == '\"')
		{
			if (!(*quote))
				(*quote) = 1;
			else if ((*quote) == 1)
				(*quote) = 0;
		}
	}
}

// static void	read_quote(char **str, int *quote)
// {
// 	char	*read_temp;

// 	while ((*quote))
// 	{
// 		read_temp = readline("> ");
// 		find_quote(read_temp, -1, quote);
// 		*str = ft_strjoinl(*str, read_temp);
// 		if (!(*str))
// 			error(0);
// 	}
// }

char	**continue_quote(char *str)
{
	int		i;
	int		quote;
	char	**temp;

	i = -1;
	quote = 0;
	find_quote(str, -1, &quote);
	if (quote)
		//return error (quote가 제대로 처리 되지 않았습니다.)// read_quote(&str, &quote);
	//"사이에 $환경변수 찾아서 바꾸기"
	//->env에서 매줄 =까지 같이 검사하기
	//$후 없으면 그냥 빈줄 출력
	temp = ft_split_quote(str, '|', 0);
	if (!temp)
		error(0);
	free(str);
	return (temp);
}
