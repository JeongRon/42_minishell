/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:35:30 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/22 16:20:45 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 받은 문자열을 확인하면서 quote가 제대로 닫혔는지 확인하는 함수.
** void
**
** @param		str		입력받은 명령어(문자열)
** @param		i		문자열의 시작 위치 default(0)
** @param		quote	quote가 제대로 닫혔는지 확인해주는 flag
*/

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
		else if (str[i] == '\"')
		{
			if (!(*quote))
				(*quote) = 1;
			else if ((*quote) == 1)
				(*quote) = 0;
		}
	}
}

/*
** str에 있는 redirection을 구분해서 ' '으로 구분해주는 함수
** char *
** 나누어진 문자열을 만들어서 리턴
**
** @param		str		입력받은 명령어(문자열)
** @value		flag	redirection이 중복되어서 나오는지 확인하는 변수
*/

static char	*distinguish_redirection(char *str)
{
	int		i;
	int		j;
	int		quote;
	int		flag;
	char	*temp;

	i = -1;
	j = 0;
	quote = 0;
	flag = 0;
	while (str[++i])
	{
		if (f_q(str[i], &quote) && quote != 0)
			continue ;
		if (str[i] == '>')
		{
			if (flag)
				error("bash: syntax error near unexpected token `>'");
			flag = 1;
			if (str[i + 1] && str[i + 1] == '>')
				i++;
			else if (str[i + 1] && str[i + 1] == '<')
				error("bash: syntax error near unexpected token `<'");
			j += 2;
		}
		else if (str[i] == '<')
		{
			if (flag)
				error("bash: syntax error near unexpected token `<'");
			flag = 1;
			if (str[i + 1] && str[i + 1] == '>')
				error("bash: syntax error near unexpected token `>'");
			else if (str[i + 1] && str[i + 1] == '<')
				i++;
			j += 2;
		}
		else
			flag = 0;
	}
	j += j + i;
	temp = (char *)ft_malloc(sizeof(char) * (j + 1));
	temp[j] = '\0';
	i = -1;
	j = -1;
	while (str[++i])
	{
		j++;
		if (f_q(str[i], &quote) && quote != 0)
			temp[j] = str[i];
		else if (str[i] == '>' || str[i] == '<')
		{
			temp[j++] = ' ';
			temp[j] = str[i];
			if ((str[i] == '>' && str[i + 1] && str[i + 1] == '>') || \
			(str[i] == '<' && str[i + 1] && str[i + 1] == '<'))
			{
				i++;
				j++;
				temp[j] = str[i];
			}
			j++;
			temp[j] = ' ';
		}
		else
			temp[j] = str[i];
	}
	return (temp);
}

/*
** quote가 제대로 닫쳤는지 확인하고 redirection을 구분해주고 '|' 단위로 나누어 주는 함수
** char **
** '|'단위로 나누어진 이중 문자열을 리턴한다.
**
** @param		str		입력받은 명령어(문자열)
*/

char	**continue_quote(char *str)
{
	int		i;
	int		quote;
	char	**temp;
	char	*div_redirect;

	i = -1;
	quote = 0;
	find_quote(str, -1, &quote);
	if (quote)
		error("bash: qutoe did not close");
	div_redirect = distinguish_redirection(str);
	free(str);
	temp = ft_split_quote(div_redirect, '|', 0);
	if (!temp)
		error("bash: system error(malloc fail)");
	free(div_redirect);
	return (temp);
}
