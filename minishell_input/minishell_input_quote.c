/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:35:30 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/18 16:52:36 by dongmiki         ###   ########.fr       */
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

char	*distinguish_redirection_part2(int i, int j, char *str, int quote)
{
	char	*temp;

	temp = (char *)ft_malloc(sizeof(char) * (j + 1));
	temp[j] = '\0';
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
				temp[++j] = str[++i];
			j++;
			temp[j] = ' ';
		}
		else
			temp[j] = str[i];
	}
	return (temp);
}

static void	distinguish_redirection_count(char *str, int *i, int *j, int *flag)
{
	if (str[*i] == '>')
	{
		if (*flag)
			error("bash: syntax error near unexpected token `>'", 258);
		*flag = 1;
		if (str[*i + 1] && str[*i + 1] == '>')
			(*i)++;
		else if (str[*i + 1] && str[*i + 1] == '<')
			error("bash: syntax error near unexpected token `<'", 258);
		*j += 2;
	}
	else if (str[*i] == '<')
	{
		if (*flag)
			error("bash: syntax error near unexpected token `<'", 258);
		*flag = 1;
		if (str[*i + 1] && str[*i + 1] == '>')
			error("bash: syntax error near unexpected token `>'", 258);
		else if (str[*i + 1] && str[*i + 1] == '<')
			(*i)++;
		*j += 2;
	}
	else
		*flag = 0;
}

static char	*distinguish_redirection(char *str, int i, int j, int quote)
{
	int		flag;

	flag = 0;
	while (str[++i])
	{
		if (f_q(str[i], &quote) && quote != 0)
			continue ;
		distinguish_redirection_count(str, &i, &j, &flag);
	}
	return (distinguish_redirection_part2(-1, j + i, str, quote));
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
		error("bash: qutoe did not close", 1);
	div_redirect = distinguish_redirection(str, -1, 0, 0);
	temp = ft_split_quote(div_redirect, '|', 0);
	free(div_redirect);
	if (!temp)
		error("bash: system error(malloc fail)", 1);
	return (temp);
}
