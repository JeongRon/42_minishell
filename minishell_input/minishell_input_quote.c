/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:35:30 by dongmiki          #+#    #+#             */
/*   Updated: 2023/08/21 22:45:21 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*distinguish_redrection(char *str)
{
	int		i;
	int		j;
	int		quote;
	int		flag;
	char	*temp;

	i = -1;
	j = 0;
	quote = 0;
	flag = 0;//redirection이 중복되어서 나오는가
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
			{
				j += 2;
				i++;//>>
			}
			else if (str[i + 1] && str[i + 1] == '<')
				error("bash: syntax error near unexpected token `<'");
			else
				j += 2;//>
		}
		else if (str[i] == '<')
		{
			if (flag)
				error("bash: syntax error near unexpected token `<'");
			flag = 1;
			if (str[i + 1] && str[i + 1] == '>')
				error("bash: syntax error near unexpected token `>'");
			else if (str[i + 1] && str[i + 1] == '<')
			{
				i++;
				j += 2;//<<
			}
			else
				j += 2;//<
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
		else if (str[i] == '>')
		{
			temp[j++] = ' ';
			temp[j] = str[i];
			if (str[i + 1] && str[i + 1] == '>')
			{
				i++;//>>
				j++;
				temp[j] = str[i];
				j++;
				temp[j] = ' ';
			}
			else
			{
				j++;//>	
				temp[j] = ' ';
			}
		}
		else if (str[i] == '<')
		{
			temp[j++] = ' ';
			temp[j] = str[i];
			if (str[i + 1] && str[i + 1] == '<')
			{
				i++;//<<
				j++;
				temp[j] = str[i];
				j++;
				temp[j] = ' ';
			}
			else
			{
				j++;//<
				temp[j] = ' ';
			}
		}
		else
			temp[j] = str[i];
	}
	return (temp);
}

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
	//"사이에 $환경변수 찾아서 바꾸기"
	//->env에서 매줄 =까지 같이 검사하기
	//$후 없으면 그냥 빈줄 출력
	div_redirect = distinguish_redrection(str);
	free(str);
	temp = ft_split_quote(div_redirect, '|', 0);
	if (!temp)
		error("bash: system error(malloc fail)");
	free(div_redirect);
	return (temp);
}
