/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:07:26 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/22 16:23:30 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_split_quote에서 사용하는 free함수
** int
**
** @param		str		만들고 있는 이중 문자열
** @param		count	문자열 겟수
*/

int	check_null(char **str, int count)
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

/*
** 제거할 quote의 갯수를 새는 함수
** int
** 제거할 quote의 갯수를 샌다.
**
** @param		str		quote를 제거할 문자열
*/

static int	del_quote_num(char *str)
{
	int		i;
	int		quote;
	int		num_quote;

	quote = 0;
	num_quote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if ((quote == 0 && f_q(str[i], &quote) && quote != 0) || \
			(quote != 0 && f_q(str[i], &quote) && quote == 0))
				num_quote++;
		}
	}
	return (num_quote);
}

/*
** 문자열에서 quote를 제거해주는 함수
** quote안에 있는 quote는 제거하지 않는다.
** 받은 문자열 str의 메모리 할당을 해제해준다.
** char *
** str에서 quote를 제거하고 그 값을 반환한다.
**
** @param		str		quote를 제거할 문자열
*/

char	*del_quote(char *str)
{
	int		i;
	int		j;
	int		quote;
	int		num_quote;
	char	*temp;

	num_quote = del_quote_num(str);
	temp = (char *)ft_malloc(sizeof(char) * (ft_strlen(str) - num_quote + 1));
	quote = 0;
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if ((quote == 0 && f_q(str[i], &quote) && quote != 0) || \
			(quote != 0 && f_q(str[i], &quote) && quote == 0))
				continue ;
		}
		temp[++j] = str[i];
	}
	temp[++j] = '\0';
	free(str);
	return (temp);
}
