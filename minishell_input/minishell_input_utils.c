/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:07:26 by dongmiki          #+#    #+#             */
/*   Updated: 2023/09/18 16:53:27 by dongmiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
